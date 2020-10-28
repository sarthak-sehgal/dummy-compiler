/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "parser.h"

bool helper(parse_tree_node *root, grammar *G, token_node **ts, pda_stack *stack);
bool parse_tree_helper(pda_stack *stack, token_node *ts_pointer, grammar *G, parse_tree_node **root);

void create_parse_tree(parse_tree_node **pt, grammar *G, token_stream *ts)
{
  *pt = NULL;
  pda_stack *stack = init_stack();
  stack_elem *start_symbol = init_stack_elem();
  start_symbol->is_terminal = false;
  start_symbol->nt = module;
  push_to_stack(stack, start_symbol);
  bool is_pt_valid = parse_tree_helper(stack, ts->head, G, pt);
  if (!is_pt_valid)
    assert(false, "source code is invalid!");
}

/*
  Creates a stack element from a grammar rule node
*/
stack_elem *gm_node_to_stack_elem(gm_node *node)
{
  stack_elem *el = init_stack_elem();
  el->is_terminal = node->is_terminal;
  if (el->is_terminal)
    el->t = (node->gmt).t;
  else
    el->nt = (node->gmt).nt;
  return el;
}

/*
  Creates a parse tree node from a PDA stack element
*/
parse_tree_node *stack_elem_to_pt_node(stack_elem *st_el)
{
  parse_tree_node *pt_node = init_pt_node();
  if (st_el->is_terminal)
  {
    pt_node->t = st_el->t;
    pt_node->is_terminal = true;
  }
  else
  {
    pt_node->is_terminal = false;
    pt_node->nt = st_el->nt;
  }
  return pt_node;
}

/*
  * Constructs the parse tree on the fly.
  * The method returns true when a parse tree can be constructed for the given stack configuration and
    the given token stream (starting from ts_pointer).
  * The idea is that whenever a stack element is popped out (terminal or nonterminal), it has to be added
    to the parse tree as a child. For this, we store the parent of each element in stack.
  * The case to be handled is when we have added some children of a node on the fly while popping out elements
    in the PDA but later on it turns out that the rule is invalid. For this, whenever we try a different rule for
    a nonterminal, we make sure to first remove all its existing children.
*/
bool parse_tree_helper(pda_stack *stack, token_node *ts_pointer, grammar *G, parse_tree_node **root)
{
  // if stack is empty and token stream is completely read, return true
  if (stack->size == 0 && ts_pointer == NULL)
    return true;

  // if either stack is empty or stream is completely read, return false
  // note that we just checked above that they both can't be true at the same time
  if (stack->size == 0 || ts_pointer == NULL)
    return false;

  stack_elem *st_top = stack->top;
  // if the stack's top element is a terminal, check it with the token stream pointer
  if (st_top->is_terminal)
  {
    if (st_top->t == EPS || st_top->t == ts_pointer->token_name)
    {
      terminal top_t = st_top->t;

      // connect the terminal with its parent
      parse_tree_node *pt_node = stack_elem_to_pt_node(st_top);
      pt_node->token = ts_pointer;
      if (st_top->par_node != NULL)
        add_pt_child(st_top->par_node, pt_node);
      pop_from_stack(stack);

      // if terminal is epsilon, do not move the token stream pointer
      if (top_t == EPS)
        return parse_tree_helper(stack, ts_pointer, G, root);
      // if terminal matches token stream pointer, move it to the next element and check
      else
        return parse_tree_helper(stack, ts_pointer->next, G, root);
    }
    return false;
  }

  nonterminal nt = st_top->nt;
  // create node for the element that is being popped
  parse_tree_node *curr_node = stack_elem_to_pt_node(st_top);

  // add the current node as child of its parent
  parse_tree_node *parent = st_top->par_node;
  if (parent != NULL)
    add_pt_child(parent, curr_node);

  // set root element for the tree if it is not set yet
  if ((*root) == NULL)
    *root = curr_node;

  pop_from_stack(stack);

  // search for the nonterminal in grammar and try each rule
  for (int i = 0; i < G->curr_num; i++)
  {
    gm_prod_rule curr_rule = (G->rules)[i];
    if (curr_rule.lhs != nt)
      continue;

    // before trying a new rule, remove the existing children of the current node
    // children may exist when previously we tried a rule but it did not work
    remove_pt_children(curr_node);

    // create a copy of the current stack each time
    // this is because we want to kind of pass the stack "by value"
    // we need a copy as we are dealing with pointers
    pda_stack *new_stack = copy_stack(stack);
    gm_node *rule_rhs = curr_rule.rhs;
    int rule_len = 1;
    while (rule_rhs->next)
    {
      rule_len++;
      rule_rhs = rule_rhs->next;
    }
    while (rule_rhs)
    {
      stack_elem *st_el = gm_node_to_stack_elem(rule_rhs);
      st_el->par_node = curr_node;
      push_to_stack(new_stack, st_el);
      rule_rhs = rule_rhs->prev;
    }

    // check if the current rule works
    if (parse_tree_helper(new_stack, ts_pointer, G, root))
    {
      curr_node->num_children = rule_len;
      curr_node->g_rule_idx = i;
      // delete_stack(new_stack);
      return true;
    }

    // deallocate the stack copy created if the rule does not work
    delete_stack(new_stack);
  }

  return false;
}

void set_declaration_types(parse_tree_node *root, hash_map *type_exp_table, error_container *err_container, int depth)
{
  if (root->is_terminal)
    return;
  if (root->is_terminal == false && root->nt == assignStmtGrp)
    return;

  if (root->is_terminal == false && root->nt == decStmt)
  {
    id_type stmt_type = get_id_type_from_dec_stmt_node(root);
    parse_tree_node *node = (root->children)[0];
    if (stmt_type == primitive)
    {
      set_table_entry_for_prim_stmt(node, type_exp_table);
    }
    else if (stmt_type == array)
    {
      set_table_entry_for_arr_stmt(node, type_exp_table);
    }
    else if (stmt_type == jag_array)
    {
      set_table_entry_for_jag_arr_stmt(node, type_exp_table, err_container, depth + 1);
    }
    else
    {
      assert(false, "[set_declaration_types] invalid statement type");
    }
    return;
  }

  for (int i = 0; i < root->num_children; i++)
    set_declaration_types((root->children)[i], type_exp_table, err_container, depth + 1);
}

void set_type_errors(parse_tree_node *root, hash_map *type_exp_table, error_container *err_container, int depth)
{
  if (root->is_terminal)
    return;
  if (root->is_terminal == false && root->nt == decStmtGrp)
    return;

  if (root->nt == assignStmt)
  {
    set_assignment_errors(root, type_exp_table, err_container, depth);
    return;
  }

  for (int i = 0; i < root->num_children; i++)
    set_type_errors((root->children)[i], type_exp_table, err_container, depth + 1);
}

void traverse_parse_tree(parse_tree_node *tree_root, hash_map *type_exp_table, error_container *err_container)
{
  set_declaration_types(tree_root, type_exp_table, err_container, 0);
  set_type_errors(tree_root, type_exp_table, err_container, 0);
}