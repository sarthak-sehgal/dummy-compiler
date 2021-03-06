/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "print.h"

void print_primitive_type_exp(primitive_id_entry *data);
void print_array_type_exp(array_id_entry *data);
void print_jag_arr_type_exp(jagged_arr_id_entry *data);

void print_rule(gm_prod_rule *rule)
{
  char *buffer = calloc(50, sizeof(char));
  assert(buffer != NULL, "[print_rule] not enough memory");
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
  buffer = NULL;
}

void print_grammar(grammar *G)
{
  char *buffer = calloc(100, sizeof(char));
  assert(buffer != NULL, "[print_grammar] not enough memory");
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
  buffer = NULL;
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
    assert(token_name != NULL, "[print_token_stream] not enough memory");
    while (node)
    {
      get_t_name(node->token_name, token_name);
      printf("(%d, %s, %s), ", node->line_num, node->lexeme, token_name);
      node = node->next;
    }

    printf("\n--- End Token Stream ---\n");
    free(token_name);
    token_name = NULL;
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
    assert(token_name != NULL, "[print_token_stream] not enough memory");
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
    token_name = NULL;
  }
}

void print_tree_node(parse_tree_node *node, int depth, bool print_symbol)
{
  char *buffer = (char *)calloc(100, sizeof(char));
  assert(buffer != NULL, "[print_tree_node] not enough memory");
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
    free(buffer);
    buffer = NULL;
    return;
  }
  printf("(tok %s, ", buffer);
  if (node->is_terminal)
  {
    printf("T, lex %s, line %d, dep %d)", node->token->lexeme, node->token->line_num, depth);
  }
  else
  {
    printf("NT, dep %d, gr_idx %d", depth, node->g_rule_idx);
    if (node->type_exp != NULL)
    {
      printf(", ");
      if (node->type_exp->type == primitive)
        print_primitive_type_exp(node->type_exp->prim_entry);
      else if (node->type_exp->type == array)
        print_array_type_exp(node->type_exp->arr_entry);
      else if (node->type_exp->type == jag_array)
        print_jag_arr_type_exp(node->type_exp->jag_arr_entry);
      else
        assert(false, "[print_tree_node] uknown type node->type_exp->type");
    }
    printf(")");
  }
  free(buffer);
  buffer = NULL;
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
  assert(buffer != NULL, "[print_pda_stack] not enough memory");
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
  free(buffer);
  buffer = NULL;
}

void print_primitive_type_exp(primitive_id_entry *data)
{
  printf("<type=");
  if (data->type == integer)
    printf("integer");
  else if (data->type == real)
    printf("real");
  else if (data->type == boolean)
    printf("boolean");
  else
    assert(false, "[print_primitive_type] unknown primitive type");
  printf(">");
}

void print_array_type_exp(array_id_entry *data)
{
  printf("<type=rectangularArray, dimensions=%d, ", data->num_dimensions);
  for (int i = 0; i < data->num_dimensions; i++)
  {
    char *range_beg = ((data->range_start)[i])->lexeme;
    char *range_end = ((data->range_end)[i])->lexeme;
    assert(range_beg != NULL && range_end != NULL, "[print_array_type_exp] invalid range");
    printf("range_R%d=(%s,%s), ", i + 1, range_beg, range_end);
  }
  printf("basicElementType=integer>");
}

void print_jag_arr_type_exp(jagged_arr_id_entry *data)
{
  printf("<type=jaggedArray, dimensions=%d, range_R1=(%d, %d), range_R2=(", data->num_dimensions, data->range_start, data->range_end);

  for (int i = 0; i < data->num_rows; i++)
  {
    int *sz = (data->sizes)[i];
    assert(sz != NULL, "[print_jag_arr_type_exp] invalid size");
    if (data->num_dimensions == 2)
    {
      printf("%d", sz[0]);
    }
    else
    {
      printf("%d [", sz[0]);
      for (int j = 0; j < sz[0]; j++)
      {
        printf("%d", sz[j + 1]);
        if (j < sz[0] - 1)
          printf(", ");
      }
      printf("]");
    }
    if (i < data->num_rows - 1)
      printf(", ");
  }
  printf("), basicElementType=integer>");
}

void print_primitive_type(primitive_id_entry *data)
{
  printf("\tprim\t|\tnot_applicable\t|\t");
  print_primitive_type_exp(data);
  printf("\n");
}

void print_array_type(array_id_entry *data)
{
  printf("\tarr\t|\t");
  if (data->is_static)
    printf("static\t\t|");
  else
    printf("dynamic\t\t|");

  printf("\t");
  print_array_type_exp(data);
  printf("\n");
}

void print_jag_arr_type(jagged_arr_id_entry *data)
{
  printf("\tJA\t|\tnot_applicable\t|\t");
  print_jag_arr_type_exp(data);
  printf("\n");
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
      print_jag_arr_type(data->jag_arr_entry);
    }
    else
    {
      assert(false, "[print_type_exp_table] unknown data type");
    }
    key_root = key_root->next;
    count++;
  }
  delete_map_node_list(key_root);
  printf("\nTotal number of VALID variables: %d", count);
  printf("\n\n*****NOTE: Type expression for variables having error in declaration is not shown*****");
  printf("\n\n---------- END TYPE EXPRESSION TABLE ----------\n\n");
}

void print_invalid_vars(invalid_vars_struct *invalid_vars)
{
  printf("\n\n---------- INVALID VARS ----------\n\n");
  int count = invalid_vars->count;
  if (count == 0)
  {
    printf("No invalid variable declaration found.");
    printf("\n\n---------- END INVALID VARS ----------\n\n");
    return;
  }
  for (int i = 0; i < count; i++)
  {
    printf("%d. %s\n", i + 1, (invalid_vars->lexeme)[i]);
  }
  printf("\n\n---------- END INVALID VARS ----------\n\n");
}

void print_id_type(primitive_id_type type)
{
  if (type == integer)
    printf("integer");
  else if (type == real)
    printf("real");
  else if (type == boolean)
    printf("boolean");
  else
    assert(false, "[print_id_type] unknown type");
}

void print_errors(error_container *err_container)
{
  if (err_container->curr_num == 0)
  {
    printf("\nNo error found!\n");
    return;
  }
  printf("\n\n---------- BEGIN ERRORS ----------\n\n");
  char *error_msg = (char *)calloc(31, sizeof(char));
  assert(error_msg != NULL, "[print_errors] not enough memory");
  for (int i = 0; i < err_container->curr_num; i++)
  {
    error_elem *error = (err_container->errors_arr)[i];
    get_error_string(error->err_type, error_msg);
    printf("\n%d. Line %d, Statement Type: ", i + 1, error->parse_tree_depth);
    if (error->statement_type == decStmt)
      printf("declaration");
    else
      printf("assignment");

    if (error->operation_token)
    {
      printf(", Operator: %s", error->operation_token->lexeme);
    }
    else
      printf(", Operator: ***");
    if (error->operand1_lexeme)
    {
      printf(", Op1: (%s, ", error->operand1_lexeme);
      print_id_type(error->operand1_type);
      printf(")");
    }
    else
    {
      printf(", Op1: ***");
    }
    if (error->operand2_lexeme)
    {
      printf(", Op2: (%s, ", error->operand2_lexeme);
      print_id_type(error->operand2_type);
      printf(")");
    }
    else
      printf(", Op2: ***");
    printf(", Tree depth: %d, Error: %s\n", error->parse_tree_depth, error_msg);
  }
  free(error_msg);
  error_msg = NULL;
  printf("\n\n---------- END ERRORS ----------\n\n");
}