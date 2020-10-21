/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "print.h"

void print_rule(gm_prod_rule *rule)
{
  char *buffer = calloc(50, sizeof(char));
  get_nt_name(rule->lhs, buffer);
  printf("%s -> ", buffer);

  gm_node *head = rule->rhs;
  while (head)
  {
    if (head->is_terminal)
    {
      get_t_name(head->gmt.t, buffer);
      printf("%s ", buffer);
    }
    else
    {
      get_nt_name(head->gmt.nt, buffer);
      printf("%s ", buffer);
    }

    head = head->next;
  }

  free(buffer);
}

void print_grammar(grammar *G)
{
  char *buffer = calloc(100, sizeof(char));
  get_nt_name(G->st_symbol, buffer);
  printf("\n--- GRAMMAR ---\n\n Start symbol: %s", buffer);
  printf("\n\nRules (%d):\n", G->curr_num);
  for (int i = 0; i < G->curr_num; i++)
  {
    print_rule(&(G->rules[i]));
    printf("\n");
  }
  printf("\n---- END GRAMMAR ---\n");

  free(buffer);
}

void print_token_stream(token_stream *ts)
{
  if (!ts->head)
  {
    printf("Token stream is empty.\n");
    return;
  }
  else
  {
    printf("\n--- Begin Token Stream ---\n");
    token_node *node = ts->head;
    char *token_name = (char *)calloc(200, sizeof(char));
    while (node)
    {
      get_t_name(node->token_name, token_name);
      printf("(%d, %s, %s), ", node->line_num, node->lexeme, token_name);
      node = node->next;
    }

    printf("\n--- End Token Stream ---\n");
    free(token_name);
  }
}

void fancy_print_token_stream(token_stream *ts)
{
  if (!ts->head)
  {
    printf("Token stream is empty!\n");
    return;
  }
  else
  {
    printf("\n--- Begin Token Stream ---\n");
    int prev_line_num = 0;
    token_node *node = ts->head;
    char *token_name = (char *)calloc(200, sizeof(char));
    while (node)
    {
      if (node->line_num != prev_line_num)
      {
        printf("\n Line %d: ", node->line_num);
        prev_line_num = node->line_num;
      }
      get_t_name(node->token_name, token_name);
      printf("(%s, %s), ", node->lexeme, token_name);
      node = node->next;
    }

    printf("\n--- End Token Stream ---\n");
    free(token_name);
  }
}

void print_tree_node(parse_tree_node *node, int depth, bool print_symbol)
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
  if (print_symbol)
  {
    printf("%s", buffer);
    return;
  }
  printf("(tok %s, ", buffer);
  if (node->is_terminal)
  {
    printf("T, lex %s, line %d, dep %d)", node->token->lexeme, node->token->line_num, depth);
  }
  else
  {
    // TO DO: PRINT TYPE EXPRESSION!
    printf("NT, dep %d, gr_idx %d)", depth, node->g_rule_idx);
  }
}

void print_pt_helper(parse_tree_node *node, int depth, bool print_symbol)
{
  printf("\n");
  for (int i = 0; i < depth; i++)
    printf("|  ");
  printf("+-- ");
  print_tree_node(node, depth, print_symbol);
  for (int i = 0; i < node->num_children; i++)
  {
    print_pt_helper((node->children)[i], depth + 1, print_symbol);
  }
}

void print_parse_tree(parse_tree_node *root)
{
  if (root == NULL)
  {
    printf("Tree is empty!\n");
    return;
  }
  printf("\n\n--- Begin Parse Tree ---\n\n");
  print_tree_node(root, 0, false);
  for (int i = 0; i < root->num_children; i++)
  {
    print_pt_helper((root->children)[i], 0, false);
  }
  printf("\n\n--- End Parse Tree ---\n\n");
}

void print_parse_tree_symbols(parse_tree_node *root)
{
  if (root == NULL)
  {
    printf("Tree is empty!\n");
    return;
  }
  printf("\n--- Begin Parse Tree ---\n");
  print_tree_node(root, 0, true);
  for (int i = 0; i < root->num_children; i++)
  {
    print_pt_helper((root->children)[i], 0, true);
  }
  printf("\n--- End Parse Tree ---\n");
}

void print_pda_stack(pda_stack *st)
{
  printf("\n PDA stack: ");
  stack_elem *temp = st->top;
  char *buffer = (char *)calloc(200, sizeof(200));
  while (temp)
  {
    if (temp->is_terminal)
    {
      get_t_name(temp->t, buffer);
    }
    else
    {
      get_nt_name(temp->nt, buffer);
    }
    printf("%s, ", buffer);
    temp = temp->prev;
  }
  printf("\n");
}

void print_primitive_type(primitive_id_entry *data)
{
  printf("\t0\t|\tnot_applicable\t|\t<type=");
  if (data->type == integer)
    printf("integer");
  else if (data->type == real)
    printf("real");
  else if (data->type == boolean)
    printf("boolean");
  else
    assert(false, "[print_primitive_type] unknown primitive type");
  printf(">\n");
}

void print_array_type(array_id_entry *data)
{
  printf("\t1\t|\t");
  if (data->is_static)
    printf("static\t\t|");
  else
    printf("dynamic\t\t|");

  printf("\t<type=rectangularArray, dimensions=%d, ", data->num_dimensions);
  for (int i = 0; i < data->num_dimensions; i++)
  {
    // TO DO: resolve lexemes for dynamic arrays
    char *range_beg = ((data->range_start)[i])->lexeme;
    char *range_end = ((data->range_end)[i])->lexeme;
    printf("range_R%d=(%s,%s), ", i + 1, range_beg, range_end);
  }
  printf("basicElementType=integer>\n");
}

void print_type_exp_table(hash_map *type_exp_table)
{
  printf("\n\n---------- BEGIN TYPE EXPRESSION TABLE ----------\n\n");
  printf("\tField 1\t|\tField 2\t|\tField 3\t\t|\tField 4\n");
  map_node *key_root = get_all_map_nodes(type_exp_table);
  int count = 0;
  while (key_root)
  {
    printf("\t%s\t|", key_root->string);
    type_exp_table_entry *data = key_root->data;
    if (data->type == primitive)
    {
      print_primitive_type(data->prim_entry);
    }
    else if (data->type == array)
    {
      print_array_type(data->arr_entry);
    }
    else if (data->type == jag_array)
    {
      // TO DO
    }
    else
    {
      assert(false, "[print_type_exp_table] unknown data type");
    }
    key_root = key_root->next;
    count++;
  }
  printf("\nTotal number of variables: %d", count);
  printf("\n\n---------- END TYPE EXPRESSION TABLE ----------\n\n");
}