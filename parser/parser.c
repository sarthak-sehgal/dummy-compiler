/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "parser.h"

bool helper(parse_tree_node *root, grammar *G, token_node **ts, pda_stack *stack);
bool is_valid(pda_stack *stack, token_node *ts_pointer, grammar *G, parse_tree_node **root);

void create_parse_tree(parse_tree_node *pt, grammar *G, token_stream *ts)
{
  pt = NULL;

  printf("\n--- Begin Parser ---\n");
  pda_stack *stack = init_stack();
  stack_elem *start_symbol = init_stack_elem();
  start_symbol->is_terminal = false;
  start_symbol->nt = module;
  push_to_stack(stack, start_symbol);

  if (is_valid(stack, ts->head, G, &pt))
  {
    printf("\nVALID!\n");
  }
  else
  {
    printf("\nOOOOOF INVALID >.<!\n");
  }

  printf("\n--- End Parser ---\n");
}

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

parse_tree_node *gm_node_to_pt_node(gm_node *node)
{
  parse_tree_node *pt_node = init_pt_node();
  pt_node->num_children = 0;
  pt_node->is_terminal = node->is_terminal;
  if (pt_node->is_terminal)
    pt_node->t = (node->gmt).t;
  else
    pt_node->nt = (node->gmt).nt;

  return pt_node;
}

void print_pt_node(parse_tree_node *node)
{
  char *buffer = (char *)calloc(100, sizeof(char));
  if (node->is_terminal)
  {
    get_t_name(node->t, buffer);
  }
  else
  {
    get_nt_name(node->nt, buffer);
  }
  printf("%s", buffer);
}

void print_term(gm_node *term)
{
  char *buffer = (char *)calloc(100, sizeof(char));
  if (term->is_terminal)
  {
    get_t_name(term->gmt.t, buffer);
  }
  else
  {
    get_nt_name(term->gmt.nt, buffer);
  }
  printf("%s", buffer);
}

void print_token1(token_node *node)
{
  char *buffer = (char *)calloc(200, sizeof(char));
  get_t_name(node->token_name, buffer);
  printf("%s", buffer);
}

bool helper(parse_tree_node *root, grammar *G, token_node **ts, pda_stack *stack)
{
  // print_pt_node(root);
  // printf("\n");
  if (stack->size > 0 && stack->top->is_terminal && stack->top->t == EPS)
    pop_from_stack(stack);
  if (ts == NULL && stack->size == 0)
  {
    printf("Token stream completely read!\n");
    return true;
  }
  if (ts == NULL || stack->size == 0)
  {
    // printf("Stack is empty!\n");
    return false;
  }

  stack_elem *top = stack->top;
  if (top->is_terminal)
  {
    printf("Terminal found! %s\n", (*ts)->lexeme);
    if (top->t == (*ts)->token_name)
    {
      pop_from_stack(stack);
      *ts = (*ts)->next;
      printf("\nReturning true!\n");
      return true;
    }
    printf("\nReturning false!\n");
    return false;
  }

  nonterminal top_nt = top->nt;
  token_node *ts_head = *ts;

  pop_from_stack(stack);
  for (int i = 0; i < G->curr_num; i++)
  {
    gm_prod_rule rule = (G->rules)[i];
    if (rule.lhs == top_nt)
    {
      // push_to_stack(stack, rule.rhs);
      // add_pt_children(root, rule.rhs);
      // bool res = true;
      // for (int i = 0; i < rule.len; i++)
      // {
      //   res = res && helper((root->children)[i], G, curr_token, stack);
      //   if (res) {
      //     pop_from_stack(stack);
      //     curr_token = curr_token->next;
      //   }
      // }
      // if (res) {
      //   ts = curr_token;
      //   return true;
      // }

      // curr_token = ts;
      // remove_pt_children(root, rule->rhs);
      // pop_from_stack(stack, rule->rhs);

      gm_node *term = rule.rhs;
      int count = 0;
      bool res = true;
      printf("\n On ");
      print_token1(*ts);
      printf("\nTrying ");
      print_rule(&rule);
      printf("\n");
      while (term)
      {
        push_to_stack(stack, gm_node_to_stack_elem(term));
        add_pt_child(root, gm_node_to_pt_node(term));

        res = res && helper((root->children)[count], G, ts, stack);

        if (!res)
        {
          pop_from_stack(stack);
          remove_pt_children(root);
          *ts = ts_head;
          break;
        }

        count++;
        term = term->next;
      }

      if (res)
      {
        root->g_rule_idx = i;
        root->num_children = count;
        return true;
      }
    }
  }

  stack_elem *top_copy = init_stack_elem();
  top_copy->is_terminal = false;
  top_copy->nt = top_nt;
  push_to_stack(stack, top_copy);
  free(top_copy);
  return false;
}

// bool helper(parse_tree_node *root, grammar *G, token_node *ts, pda_stack *stack)
// {
//   stack_elem *top = stack->top;
//   if (top == NULL)
//   {
//     if (ts == NULL)
//       return true;
//     return false;
//   }

//   if (top->is_terminal && top->t)
//   {
//     pop_from_stack(stack);
//     return helper(root, G, ts->next, stack);
//   }

//   if (top->is_terminal)
//   {
//     printf("Terminal found! %s\n", ts->lexeme);
//     if (top->t == ts->token_name)
//     {
//       pop_from_stack(stack);
//       return helper(root, G, ts->next, stack);
//     }
//     printf("\nReturning false!\n");
//     return false;
//   }

//   nonterminal top_nt = top->nt;
//   pop_from_stack(stack);

//   for (int i = 0; i < G->curr_num; i++)
//   {
//     gm_prod_rule rule = (G->rules)[i];
//     if (rule.lhs != top_nt)
//       continue;

//     gm_node *forward_it = rule.rhs;
//     gm_node *backward_it = rule.rhs;
//     while (backward_it->next)
//       backward_it = backward_it->next;

//     stack_elem *curr_top = stack->top;
//     while (forward_it)
//     {
//       push_to_stack(stack, gm_node_to_stack_elem(backward_it));
//       add_pt_child(root, gm_node_to_pt_node(forward_it));
//       forward_it = forward_it->next;
//       backward_it = backward_it->prev;
//     }
//   }
// }

void print_stack_elem(stack_elem *el)
{
  char *buffer = (char *)calloc(200, sizeof(char));
  if (el->is_terminal)
  {
    get_t_name(el->t, buffer);
  }
  else
  {
    get_nt_name(el->nt, buffer);
  }
  printf("%s", buffer);
}

bool is_valid(pda_stack *stack, token_node *ts_pointer, grammar *G, parse_tree_node **root)
{
  // char c;
  // scanf("%c", &c);
  // print_pda_stack(stack);
  if (stack->size == 0 && ts_pointer == NULL)
  {
    printf("Token stream read! :D");
    return true;
  }
  if (stack->size == 0 || ts_pointer == NULL)
  {
    printf("Stack is empty!!\n");
    return false;
  }

  // printf("\n\nOn %s, ", ts_pointer->lexeme);
  // printf("stack->top ");
  // print_stack_elem(stack->top);
  // printf(", token_name ");
  // print_token1(ts_pointer);
  // printf("\n");

  stack_elem *st_top = stack->top;
  if (st_top->is_terminal && st_top->t == EPS)
  {
    parse_tree_node *pt_node = init_pt_node();
    pt_node->num_children = 0;
    pt_node->t = EPS;
    pt_node->is_terminal = true;
    add_pt_child(st_top->par_node, pt_node);
    pop_from_stack(stack);
    return is_valid(stack, ts_pointer, G, root);
  }

  if (st_top->is_terminal)
  {
    if (st_top->t == ts_pointer->token_name)
    {
      parse_tree_node *pt_node = init_pt_node();
      pt_node->num_children = 0;
      pt_node->t = ts_pointer->token_name;
      pt_node->is_terminal = true;
      add_pt_child(st_top->par_node, pt_node);
      pop_from_stack(stack);
      bool res = is_valid(stack, ts_pointer->next, G, root);
      // if (res)
      //   printf("Returning true.\n");
      // else
      //   printf("Returning false.\n");

      return res;
    }
    // printf("Returning false.\n");
    return false;
  }

  nonterminal nt = st_top->nt;
  parse_tree_node *tree_node = init_pt_node();
  tree_node->is_terminal = false;
  tree_node->nt = nt;

  parse_tree_node *parent = st_top->par_node;

  if (parent != NULL)
  {
    add_pt_child(parent, tree_node);
  }

  if ((*root) == NULL)
    *root = tree_node;

  pop_from_stack(stack);

  for (int i = 0; i < G->curr_num; i++)
  {
    gm_prod_rule curr_rule = (G->rules)[i];
    if (curr_rule.lhs != nt)
      continue;

    remove_pt_children(tree_node);

    pda_stack *new_stack = copy_stack(stack);
    gm_node *rule_rhs = curr_rule.rhs;
    int count = 1;
    while (rule_rhs->next)
    {
      count++;
      rule_rhs = rule_rhs->next;
    }
    while (rule_rhs)
    {
      stack_elem *st_el = gm_node_to_stack_elem(rule_rhs);
      st_el->par_node = tree_node;
      push_to_stack(new_stack, st_el);
      rule_rhs = rule_rhs->prev;
    }
    // printf("Trying ");
    // print_rule(&curr_rule);
    if (is_valid(new_stack, ts_pointer, G, root))
    {
      // printf("Returning true.\n");
      tree_node->num_children = count;
      tree_node->g_rule_idx = i;
      return true;
    }

    delete_stack(new_stack);
  }

  // printf("Returning false.\n");
  return false;
}