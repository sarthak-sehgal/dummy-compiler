/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "type_exp_table.h"

hash_map *init_type_exp_table()
{
  hash_map *table = init_map(30);
  return table;
}

type_exp_table_entry *init_table_entry()
{
  type_exp_table_entry *table_entry = (type_exp_table_entry *)calloc(1, sizeof(type_exp_table_entry));
  return table_entry;
}

id_type get_id_type_from_dec_stmt_node(parse_tree_node *node)
{
  // check if it is valid declaration statement node
  if (node->is_terminal || node->nt != decStmt || node->num_children == 0)
    assert(false, "[get_id_type_from_dec_stmt_node] declaration statement node invalid.");

  node = node->children[0];
  if (node->nt == primitiveDecStmt)
    return primitive;
  if (node->nt == arrayDecStmt)
    return array;
  if (node->nt == jagArrDecStmt)
    return jag_array;

  assert(false, "[get_id_type_from_dec_stmt_node] declaration statement node invalid.");
  return 0;
}

void get_lexeme_list_helper(char ***id_list, parse_tree_node *node, int *curr_stored, int *capacity)
{
  if (node->is_terminal && node->t == ID)
  {
    // reallocate memory
    if (*curr_stored == *capacity)
    {
      *capacity *= 2;
      *id_list = (char **)realloc(*id_list, sizeof(char *) * (*capacity));
    }

    (*id_list)[(*curr_stored)] = node->token->lexeme;
    *curr_stored += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == multipleIdList || child->nt == idList || child->t == ID)
      get_lexeme_list_helper(id_list, child, curr_stored, capacity);
  }
}

char **get_lexeme_list(parse_tree_node *node, int *num_id)
{
  int capacity = 1;
  char **id_list = (char **)calloc(1, sizeof(char *));
  get_lexeme_list_helper(&id_list, node, num_id, &capacity);
  return id_list;
}

int get_nt_line_num(parse_tree_node *node)
{
  if (node->is_terminal)
    return node->token->line_num;

  return get_nt_line_num((node->children)[0]);
}

void set_table_entry_for_prim_stmt(parse_tree_node *node, hash_map *type_exp_table)
{
  // check if node is valid primitive data type node
  if (node->is_terminal || node->nt != primitiveDecStmt || node->num_children == 0)
    assert(false, "[set_table_entry_for_prim_stmt] declaration statement node invalid.");

  // get the primitive data type
  primitive_id_type prim_type;
  bool id_type_found = false;
  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == primitiveDataType)
    {
      if (child->num_children == 0)
        assert(false, "[set_table_entry_for_prim_stmt] primitiveDataType's child not found in parse tree");
      child = (child->children)[0];
      if (child->t == INTEGER)
        prim_type = integer;
      else if (child->t == REAL)
        prim_type = real;
      else if (child->t == BOOLEAN)
        prim_type = boolean;
      else
        assert(false, "[set_table_entry_for_prim_stmt] invalid primitiveDataType child in parse tree");
      id_type_found = true;
      break;
    }
  }

  if (!id_type_found)
    assert(false, "[set_table_entry_for_prim_stmt] primitive statement identifier type (integer/real/boolean) not found in parse tree");

  // get list of identifiers
  int num_id = 0;
  char **id_list = get_lexeme_list(node, &num_id);
  // for each identifier, set the table entry
  for (int i = 0; i < num_id; i++)
  {
    primitive_id_entry *prim_entry = (primitive_id_entry *)calloc(1, sizeof(primitive_id_entry));
    prim_entry->type = prim_type;
    prim_entry->lexeme = id_list[i];

    if (node->type_exp == NULL)
    {
      node->type_exp = (type_exp_table_entry *)calloc(1, sizeof(type_exp_table_entry));
      node->type_exp->type = primitive;
      node->type_exp->prim_entry = prim_entry;
    }

    type_exp_table_entry *entry = init_table_entry();
    entry->type = primitive;
    entry->prim_entry = prim_entry;
    insert_into_map(type_exp_table, prim_entry->lexeme, entry);
  }
  free(id_list);
  id_list = NULL;
}

void get_arr_range_info(array_id_entry *array_entry, parse_tree_node *node)
{
  if (node->nt == arrayRange)
  {
    if (array_entry->num_dimensions == array_entry->range_arr_capacity)
    {
      // reallocate
      array_entry->range_arr_capacity *= 2;
      array_entry->range_start = (token_node **)realloc(array_entry->range_start, sizeof(token_node *) * (array_entry->range_arr_capacity));
      array_entry->range_end = (token_node **)realloc(array_entry->range_end, sizeof(token_node *) * (array_entry->range_arr_capacity));
    }
    if (node->num_children < 4)
      assert(false, "[get_arr_range_info] arrayRange node has insufficient children");
    parse_tree_node *range_st_dim = (((node->children)[1])->children)[0]; // arrayRange->children[1] points to numOrId and then its first child points to NUM or ID
    parse_tree_node *range_en_dim = (((node->children)[3])->children)[0]; // arrayRange->children[3] points to numOrId and then its first child points to NUM or ID
    if (range_st_dim->t == ID || range_en_dim->t == ID)
      array_entry->is_static = false;
    (array_entry->range_start)[array_entry->num_dimensions] = range_st_dim->token;
    (array_entry->range_end)[array_entry->num_dimensions] = range_en_dim->token;

    array_entry->num_dimensions += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == arrayRangeList || child->nt == arrayRange)
      get_arr_range_info(array_entry, child);
  }
}

void set_table_entry_for_arr_stmt(parse_tree_node *node, hash_map *type_exp_table)
{
  // check if node is valid array type node
  if (node->is_terminal || node->nt != arrayDecStmt || node->num_children == 0)
    assert(false, "[set_table_entry_for_arr_stmt] declaration statement node invalid.");

  array_id_entry dummy_array_entry;
  dummy_array_entry.is_static = true;
  dummy_array_entry.num_dimensions = 0;
  dummy_array_entry.range_arr_capacity = 1;
  dummy_array_entry.range_end = (token_node **)calloc(1, sizeof(token_node *));
  dummy_array_entry.range_start = (token_node **)calloc(1, sizeof(token_node *));
  get_arr_range_info(&dummy_array_entry, node);

  // get list of identifiers
  int num_id = 0;
  char **id_list = get_lexeme_list(node, &num_id);
  // for each identifier, set the table entry
  for (int i = 0; i < num_id; i++)
  {
    array_id_entry *array_entry = (array_id_entry *)calloc(1, sizeof(array_id_entry));
    array_entry->is_static = dummy_array_entry.is_static;
    array_entry->lexeme = id_list[i];
    array_entry->num_dimensions = dummy_array_entry.num_dimensions;
    array_entry->range_arr_capacity = dummy_array_entry.range_arr_capacity;
    array_entry->range_end = dummy_array_entry.range_end;
    array_entry->range_start = dummy_array_entry.range_start;

    if (node->type_exp == NULL)
    {
      node->type_exp = (type_exp_table_entry *)calloc(1, sizeof(type_exp_table_entry));
      node->type_exp->type = array;
      node->type_exp->arr_entry = array_entry;
    }

    type_exp_table_entry *entry = init_table_entry();
    entry->type = array;
    entry->arr_entry = array_entry;
    insert_into_map(type_exp_table, id_list[i], entry);
  }
  free(id_list);
  id_list = NULL;
}

void set_jag_arr_dim_and_range(parse_tree_node *node, jagged_arr_id_entry *jag_arr_entry)
{
  if (node->nt != jagArrDecStmt)
    assert(false, "[set_jag_arr_dim_and_range] invalid parse tree node");

  parse_tree_node *range_node = NULL;
  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == jagArrRange)
    {
      range_node = child;
      break;
    }
  }

  if (range_node->nt != jagArrRange || range_node->num_children < 4)
  {
    assert(false, "[set_jag_arr_dim_and_range] jagged array range node not found or invalid");
  }

  int range_beg = string_to_num(((range_node->children)[1])->token->lexeme); // children at index 1 is the first NUM
  int range_end = string_to_num(((range_node->children)[3])->token->lexeme); // children at index 3 is the second NUM

  int num_dimensions = 0;
  for (int i = 0; i < range_node->num_children; i++)
    if (((range_node->children)[i])->t == SQOP)
      num_dimensions++;

  jag_arr_entry->num_dimensions = num_dimensions;
  jag_arr_entry->range_start = range_beg;
  jag_arr_entry->range_end = range_end;
}

int get_num_count(parse_tree_node *node)
{
  if (node->t == NUM)
    return 1;
  if (node->is_terminal)
    return 0;
  int cnt = 0;
  for (int i = 0; i < node->num_children; i++)
  {
    cnt += get_num_count((node->children)[i]);
  }

  return cnt;
}

void create_and_add_error(error_container *err_container,
                          int line_num,
                          int parse_tree_depth,
                          error_type err_type,
                          nonterminal statement_type,
                          token_node *operation_token,
                          token_node *operand1_token,
                          token_node *operand2_token,
                          char *operand1_lexeme,
                          char *operand2_lexeme)
{
  error_elem *error = init_error();
  error->line_num = line_num;
  error->statement_type = statement_type;
  error->operand1_token = operand1_token;
  error->operation_token = operation_token;
  error->operand2_token = operand2_token;
  error->parse_tree_depth = parse_tree_depth;
  error->err_type = err_type;
  error->operand1_lexeme = operand1_lexeme;
  error->operand2_lexeme = operand2_lexeme;
  add_error(err_container, error);
}

void set_jag_arr_value_sizes(parse_tree_node *node, jagged_arr_id_entry *jag_arr_entry, int *values_cnt, int max_val_count, int sizes_idx, int depth, error_container *err_container)
{
  if (node->nt == numList)
  {
    if ((*values_cnt) >= max_val_count)
    {
      create_and_add_error(err_container, get_nt_line_num(node), depth, jagArrNumListOverflow, decStmt, NULL, NULL, NULL, NULL, NULL);
      return;
    }

    int num_count = get_num_count(node);
    if (num_count == 0)
    {
      create_and_add_error(err_container, get_nt_line_num(node), depth, jagArrNumListUnderflow, decStmt, NULL, NULL, NULL, NULL, NULL);
      return;
    }

    (jag_arr_entry->sizes)[sizes_idx][(*values_cnt) + 1] = num_count;

    (*values_cnt) += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = ((node->children)[i]);
    if (child->nt == jagArrValues || child->nt == numList)
      set_jag_arr_value_sizes(child, jag_arr_entry, values_cnt, max_val_count, sizes_idx, depth, err_container);
  }
}

void set_jag_arr_sizes(parse_tree_node *node, jagged_arr_id_entry *jag_arr_entry, int *dim_idx, int depth, error_container *err_container)
{
  if (node->nt == jagArrDimDec)
  {
    if (node->num_children < 11) // should this be 12 instead
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec");

    parse_tree_node *idx_node = (node->children)[2];
    if (idx_node->t != NUM)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec: index node not 2nd child");
    int idx = string_to_num(idx_node->token->lexeme);
    if (idx < jag_arr_entry->range_start || idx > jag_arr_entry->range_end)
    {
      create_and_add_error(err_container, idx_node->token->line_num, depth, jagArrIndexOutOfBounds, decStmt, NULL, NULL, NULL, NULL, NULL);
      return;
    }

    parse_tree_node *size_node = (node->children)[6];
    if (size_node->t != NUM)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec: size node not 6th child");
    int size = string_to_num(size_node->token->lexeme);
    if (size <= 0)
    {
      create_and_add_error(err_container, idx_node->token->line_num, depth, jagArrDecSizeUnderflow, decStmt, NULL, NULL, NULL, NULL, NULL);
      return;
    }

    (jag_arr_entry->sizes)[(*dim_idx)] = (int *)calloc(size + 1, sizeof(int));
    (jag_arr_entry->sizes)[(*dim_idx)][0] = size;

    parse_tree_node *range_list = (node->children)[10];
    if (range_list->nt != jagArrValues)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec: values node not 10th child");
    int values_cnt = 0;
    set_jag_arr_value_sizes(range_list, jag_arr_entry, &values_cnt, size, *dim_idx, depth, err_container);

    (*dim_idx) += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == jagArrDimDec || child->nt == jagArrInit)
      set_jag_arr_sizes(child, jag_arr_entry, dim_idx, depth + 1, err_container);
  }
}

void set_table_entry_for_jag_arr_stmt(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth)
{
  // check if node is valid jagged array type node
  if (node->is_terminal || node->nt != jagArrDecStmt || node->num_children == 0)
    assert(false, "[set_table_entry_for_arr_stmt] declaration statement node invalid.");

  // get list of identifiers
  int num_id = 0;
  char **id_list = get_lexeme_list(node, &num_id);

  jagged_arr_id_entry dummy_jag_arr_entry;
  set_jag_arr_dim_and_range(node, &dummy_jag_arr_entry);

  int range_start = dummy_jag_arr_entry.range_start;
  int range_end = dummy_jag_arr_entry.range_end;
  if (range_end < range_start)
  {
    create_and_add_error(err_container, get_nt_line_num(node), depth, jagArrNegativeRange, decStmt, NULL, NULL, NULL, NULL, NULL);
    for (int i = 0; i < num_id; i++)
      add_invalid_var(err_container, id_list[i]);
    return;
  }

  int jag_arr_size = range_end - range_start + 1;
  dummy_jag_arr_entry.num_rows = jag_arr_size;
  dummy_jag_arr_entry.sizes = (int **)calloc(jag_arr_size, sizeof(int *));
  int dim_idx = 0;
  int prev_err_cnt = err_container->curr_num;
  set_jag_arr_sizes(node, &dummy_jag_arr_entry, &dim_idx, depth, err_container);
  int curr_err_cnt = err_container->curr_num;

  if (curr_err_cnt > prev_err_cnt)
  {
    // jagged array declaration had error so do not add type expression to table
    for (int i = 0; i < num_id; i++)
      add_invalid_var(err_container, id_list[i]);
    return;
  }

  // for each identifier, set the table entry
  for (int i = 0; i < num_id; i++)
  {
    jagged_arr_id_entry *jag_array_entry = (jagged_arr_id_entry *)calloc(1, sizeof(jagged_arr_id_entry));
    jag_array_entry->lexeme = id_list[i];
    jag_array_entry->num_dimensions = dummy_jag_arr_entry.num_dimensions;
    jag_array_entry->num_rows = dummy_jag_arr_entry.num_rows;
    jag_array_entry->range_start = dummy_jag_arr_entry.range_start;
    jag_array_entry->range_end = dummy_jag_arr_entry.range_end;
    jag_array_entry->sizes = dummy_jag_arr_entry.sizes;

    if (node->type_exp == NULL)
    {
      node->type_exp = (type_exp_table_entry *)calloc(1, sizeof(type_exp_table_entry));
      node->type_exp->type = jag_array;
      node->type_exp->jag_arr_entry = jag_array_entry;
    }

    type_exp_table_entry *entry = init_table_entry();
    entry->type = jag_array;
    entry->jag_arr_entry = jag_array_entry;
    insert_into_map(type_exp_table, id_list[i], entry);
  }
  free(id_list);
  id_list = NULL;
}

bool check_jag_arr_dimensions(parse_tree_node *node, hash_map *type_exp_table, jagged_arr_id_entry *arr_type_exp, error_container *err_container, int depth, int *dim_count, int *dim1, int *dim2)
{
  if (node->nt == numOrId)
  {
    if (*dim_count >= arr_type_exp->num_dimensions)
    {
      create_and_add_error(err_container, get_nt_line_num(node), depth, arr_type_exp->num_dimensions == 2 ? jagArr2dSizeMismatch : jagArr3dSizeMismatch, assignStmt, NULL, NULL, NULL, NULL, NULL);
      return false;
    }

    node = (node->children)[0];
    if (node->t == NUM)
    {
      int num = string_to_num(node->token->lexeme);
      int range_beg, range_end;
      if (*dim_count == 0)
      {
        range_beg = arr_type_exp->range_start;
        range_end = arr_type_exp->range_end;
        (*dim1) = num;
      }
      else
      {
        int *range = (arr_type_exp->sizes)[(*dim1 - arr_type_exp->range_start)];
        range_beg = 0;
        if (*dim_count == 1)
        {
          range_end = range[0] - 1;
          (*dim2) = num;
        }
        else
          range_end = range[1 + (*dim2)] - 1;
      }

      if (num < range_beg || num > range_end)
      {
        create_and_add_error(err_container, node->token->line_num, depth + 1, jagArrIndexOutOfBounds, assignStmt, NULL, node->token, NULL, NULL, NULL);
        return false;
      }
    }
    else if (node->t == ID)
    {
      type_exp_table_entry *identifier = find_in_map(type_exp_table, node->token->lexeme);
      if (identifier == NULL || identifier->type != primitive || identifier->prim_entry->type != integer)
      {
        create_and_add_error(err_container, node->token->line_num, depth + 1, identifier == NULL ? declarationInvalid : invalidArrayIndexType, assignStmt, NULL, node->token, NULL, NULL, NULL);
        return false;
      }
    }
    else
    {
      assert(false, "[check_jag_arr_dimensions] invalid node numOrId");
    }

    (*dim_count)++;
  }

  bool res = true;
  for (int i = 0; i < node->num_children; i++)
  {
    res = res && check_jag_arr_dimensions((node->children)[i], type_exp_table, arr_type_exp, err_container, depth + 1, dim_count, dim1, dim2);
  }

  return res;
}

bool check_array_dimensions(parse_tree_node *node, hash_map *type_exp_table, array_id_entry *arr_type_exp, error_container *err_container, int depth, int *dim_count)
{
  if (node->nt == numOrId)
  {
    if (*dim_count >= arr_type_exp->num_dimensions)
    {
      create_and_add_error(err_container, get_nt_line_num(node), depth, arrSizeMismatch, assignStmt, NULL, NULL, NULL, NULL, NULL);
      return false;
    }

    node = (node->children)[0];
    if (node->t == NUM)
    {
      int num = string_to_num(node->token->lexeme);
      token_node *range_st = (arr_type_exp->range_start)[*dim_count];
      token_node *range_en = (arr_type_exp->range_end)[*dim_count];
      if ((range_st->token_name == NUM && num < string_to_num(range_st->lexeme)) || ((range_en->token_name == NUM && num > string_to_num(range_en->lexeme))))
      {
        create_and_add_error(err_container, node->token->line_num, depth + 1, arrIndexOutOfBounds, assignStmt, NULL, node->token, NULL, NULL, NULL);
        return false;
      }
    }
    else if (node->t == ID)
    {
      type_exp_table_entry *identifier = find_in_map(type_exp_table, node->token->lexeme);
      if (identifier == NULL || identifier->type != primitive || identifier->prim_entry->type != integer)
      {
        create_and_add_error(err_container, node->token->line_num, depth + 1, identifier == NULL ? declarationInvalid : invalidArrayIndexType, assignStmt, NULL, node->token, NULL, NULL, NULL);
        return false;
      }
    }
    else
    {
      assert(false, "[check_array_dimensions] invalid node numOrId");
    }

    (*dim_count)++;
    return true;
  }

  bool res = true;
  for (int i = 0; i < node->num_children; i++)
  {
    res = res && check_array_dimensions((node->children)[i], type_exp_table, arr_type_exp, err_container, depth + 1, dim_count);
  }

  return res;
}

bool is_arr_element_valid(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth)
{
  if (node->nt != arrayElement)
    assert(false, "[is_arr_element_valid] invalid node passed");

  parse_tree_node *identifier = (node->children)[0];
  if (identifier->t != ID)
    assert(false, "[is_arr_element_valid] invalid node passed");

  type_exp_table_entry *type_exp = (type_exp_table_entry *)find_in_map(type_exp_table, identifier->token->lexeme);
  if (type_exp == NULL || type_exp->type == primitive)
  {
    create_and_add_error(err_container, identifier->token->line_num, depth + 1, type_exp == NULL ? declarationInvalid : idNotArray, assignStmt, NULL, identifier->token, NULL, NULL, NULL);
    return false;
  }
  else if (type_exp->type == array)
  {
    int dim_count = 0;
    bool res = check_array_dimensions((node->children)[2], type_exp_table, type_exp->arr_entry, err_container, depth, &dim_count);
    if (res && dim_count < type_exp->arr_entry->num_dimensions)
    {
      create_and_add_error(err_container, get_nt_line_num((node->children)[2]), depth, arrSizeMismatch, assignStmt, NULL, NULL, NULL, NULL, NULL);
      return false;
    }
    return res;
  }
  else if (type_exp->type == jag_array)
  {
    int dim_count = 0;
    int dim1 = -1;
    int dim2 = -1;
    bool res = check_jag_arr_dimensions((node->children)[2], type_exp_table, type_exp->jag_arr_entry, err_container, depth, &dim_count, &dim1, &dim2);
    if (res && dim_count < type_exp->jag_arr_entry->num_dimensions)
    {
      create_and_add_error(err_container, get_nt_line_num((node->children)[2]), depth, type_exp->jag_arr_entry->num_dimensions == 2 ? jagArr2dSizeMismatch : jagArr3dSizeMismatch, assignStmt, NULL, NULL, NULL, NULL, NULL);
      return false;
    }
    return res;
  }
  else
  {
    assert(false, "[is_arr_element_valid] type not recognized");
  }

  return true;
}

primitive_id_type get_assignment_lhs_type(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth, bool *is_error)
{
  type_exp_table_entry *type_exp = NULL;
  if (node->t == ID)
  {
    type_exp = (type_exp_table_entry *)find_in_map(type_exp_table, node->token->lexeme);
    if (type_exp == NULL || type_exp->type != primitive)
    {
      create_and_add_error(err_container, node->token->line_num, depth, type_exp == NULL ? declarationInvalid : arrSizeMismatch, assignStmt, NULL, node->token, NULL, NULL, NULL);
      *is_error = true;
      return 0;
    }
    return type_exp->prim_entry->type;
  }

  if (node->nt != assignLhs || node->num_children < 1)
    assert(false, "[get_assignment_lhs_type] invalid assignment node");

  node = (node->children)[0];
  depth += 1;

  if (node->t == ID)
  {
    type_exp = (type_exp_table_entry *)find_in_map(type_exp_table, node->token->lexeme);
    if (type_exp == NULL || type_exp->type != primitive)
    {
      create_and_add_error(err_container, node->token->line_num, depth, type_exp == NULL ? declarationInvalid : arrSizeMismatch, assignStmt, NULL, node->token, NULL, NULL, NULL);
      *is_error = true;
      return 0;
    }
    return type_exp->prim_entry->type;
  }
  if (is_arr_element_valid(node, type_exp_table, err_container, depth + 1))
  {
    return integer;
  }
  else
  {
    *is_error = true;
  }

  return 0;
}

void check_expression_compatibility(parse_tree_node *node,
                                    primitive_id_type operand1_type,
                                    primitive_id_type operand2_type,
                                    terminal operator,
                                    error_container * err_container,
                                    bool * is_error,
                                    int depth)
{

  token_node *operation_token = ((node->children)[1])->token;
  token_node *operand1_token = ((node->children)[0])->token;
  token_node *operand2_token = ((node->children)[2])->token;

  if (operator== DIV && !((operand1_type == integer && operand2_type == integer) ||
                          (operand1_type == real && operand2_type == real)))
  {
    create_and_add_error(err_container, operation_token->line_num, depth, invalidDivisionOperation, assignStmt, operation_token, operand1_token, operand2_token, ((node->children)[0])->type_exp->prim_entry->lexeme, ((node->children)[2])->type_exp->prim_entry->lexeme);
    *is_error = true;
  }
  else if (operand1_type != operand2_type)
  {
    create_and_add_error(err_container, operation_token->line_num, depth, typeMismatch, assignStmt, operation_token, operand1_token, operand2_token, ((node->children)[0])->type_exp->prim_entry->lexeme, ((node->children)[2])->type_exp->prim_entry->lexeme);
    *is_error = true;
  }
  else if ((operand1_type == boolean && (operator== PLUS || operator== MINUS || operator== DIV || operator== MUL)))
  {
    create_and_add_error(err_container, operation_token->line_num, depth, invalidBoolOperation, assignStmt, operation_token, operand1_token, operand2_token, ((node->children)[0])->type_exp->prim_entry->lexeme, ((node->children)[2])->type_exp->prim_entry->lexeme);
    *is_error = true;
  }
  else if ((operand1_type != boolean && (operator== OR || operator== AND)))
  {
    create_and_add_error(err_container, operation_token->line_num, depth, invalidArithmeticOperation, assignStmt, operation_token, operand1_token, operand2_token, ((node->children)[0])->type_exp->prim_entry->lexeme, ((node->children)[2])->type_exp->prim_entry->lexeme);
    *is_error = true;
  }
  // if(*is_error) printf("    Not compatible!\n");
  // else printf("    Compatible!\n");
  return;
}

char *concat_strings(char *string1, char *string2)
{

  if (string1 == NULL && string2 == NULL)
    return NULL;
  if (string1 == NULL)
    return string2;
  if (string2 == NULL)
    return string1;

  int new_size = strlen(string1) + strlen(string2) + 1;
  char *res = (char *)calloc(new_size, sizeof(char));
  strcat(res, string1);
  strcat(res, string2);
  return res;
}

char *convert_array_to_string(parse_tree_node *node)
{
  int num_children = node->num_children;
  if (num_children == 0)
    return NULL;
  char *res = NULL;
  char *blank = " ";
  for (int i = 0; i < num_children; i++)
  {
    if ((node->children)[i]->is_terminal)
    {

      if (res == NULL)
      {
        res = (node->children)[i]->token->lexeme;
        res = concat_strings(res, blank);
      }
      else
      {
        res = concat_strings(res, (node->children)[i]->token->lexeme);
        res = concat_strings(res, blank);
      }
      // printf("Inside convert array : %s\n", res);
    }
    else
    {
      res = concat_strings(res, convert_array_to_string((node->children)[i]));
      // printf("Inside convert array : %s\n", res);
    }
  }
  return res;
}

void set_nonterminal_type_exp(parse_tree_node *node, primitive_id_type type, char *lexeme)
{
  // create primitive entry
  primitive_id_entry *prim_entry = (primitive_id_entry *)calloc(1, sizeof(primitive_id_entry));
  prim_entry->lexeme = lexeme;
  prim_entry->type = type;

  type_exp_table_entry *type_exp_entry = init_table_entry();
  type_exp_entry->type = primitive;
  type_exp_entry->prim_entry = prim_entry;

  node->type_exp = type_exp_entry;
}

primitive_id_type get_operand_type(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth, bool *is_error)
{
  if (node->nt != operand)
    assert(false, "[get_operand_type] invalid node.");

  parse_tree_node *child = (node->children)[0];

  if (child->t == NUM) // operand -> NUM
  {
    set_nonterminal_type_exp(node, integer, child->token->lexeme);
    return integer;
  }
  else if (child->t == ID) // operand -> ID
  {
    type_exp_table_entry *identifier = (type_exp_table_entry *)find_in_map(type_exp_table, child->token->lexeme);
    if (identifier == NULL || identifier->type != primitive)
    {
      create_and_add_error(err_container, child->token->line_num, depth + 1, identifier == NULL ? declarationInvalid : arrSizeMismatch, assignStmt, NULL, child->token, NULL, NULL, NULL);
      *is_error = true;
      return 0;
    }
    set_nonterminal_type_exp(node, identifier->prim_entry->type, child->token->lexeme);
    return identifier->prim_entry->type;
  }
  else if (child->nt == arrayElement) // operand -> arrayElement
  {
    *is_error = !(is_arr_element_valid(child, type_exp_table, err_container, depth + 1));
    if (*is_error)
    {
      return 0;
    }

    char *array_element_lexeme = convert_array_to_string(child);
    set_nonterminal_type_exp(node, integer, array_element_lexeme);
    return integer;
  }
  else
  {
    assert(false, "[check_term] invalid operand node");
  }
  return 0;
}
primitive_id_type check_term(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth, bool *is_error)
{
  if (node->nt != term)
  {
    assert(false, "[check_term] invalid term node");
  }
  if (node->num_children == 1) // term -> operand
  {
    primitive_id_type operand_type = get_operand_type((node->children)[0], type_exp_table, err_container, depth + 1, is_error);

    if (*is_error)
    {
      return 0;
    }
    // printf("operand type %d\n", operand_type);
    // printf("set non term IN\n");
    set_nonterminal_type_exp(node, operand_type, ((node->children)[0])->type_exp->prim_entry->lexeme);
    // printf("set non term OUT\n");
    return operand_type;
  }
  else
  {
    // term operand (operator) term

    primitive_id_type operand1_type, operand2_type;
    // printf("get operand 1 IN\n");
    operand1_type = get_operand_type((node->children)[0], type_exp_table, err_container, depth + 1, is_error);
    // printf("get operand 1 OUT\n");
    if (*is_error)
    {
      return 0;
    }
    else
    {
      // printf("check term recur IN\n");
      operand2_type = check_term((node->children)[2], type_exp_table, err_container, depth + 1, is_error);
      // printf("check term recur OUT\n");
      if (*is_error)
      {
        return 0;
      }
    }

    //check compatibility of operand and term
    terminal operator=((node->children)[1])->t;
    check_expression_compatibility(node, operand1_type, operand2_type, operator, err_container, is_error, depth);
    if (*is_error)
    {
      return 0;
    }
    else
    {
      // printf("Set expression start \n");
      char *expression = " ";
      char *blank = " ";
      expression = concat_strings((node->children)[0]->type_exp->prim_entry->lexeme, expression);
      expression = concat_strings(expression, ((node->children)[1])->token->lexeme);
      expression = concat_strings(expression, blank);
      expression = concat_strings(expression, (node->children)[2]->type_exp->prim_entry->lexeme);
      // printf("Set expression end \n");
      // printf("set non term IN\n");
      // printf("----------------------------Expression-------------------%s\n", expression);
      set_nonterminal_type_exp(node, operator== DIV ? real : operand1_type, expression);
      // printf("set non term OUT\n");
      return operator== DIV ? real : operand1_type;
    }
  }
}

primitive_id_type get_assignment_rhs_type(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth, bool *is_error)
{
  if (node->nt != arithExpression)
  {
    assert(false, "[get_assignment_rhs_type] invalid assignment node");
  }
  if (node->num_children == 1) // arithExpression -> term
  {
    primitive_id_type operand_type = check_term((node->children)[0], type_exp_table, err_container, depth + 1, is_error);

    if (*is_error)
    {
      return 0;
    }
    set_nonterminal_type_exp(node, operand_type, (node->children)[0]->type_exp->prim_entry->lexeme);
    return operand_type;
  }
  else
  {
    // arithExpression term (operator) arithExpression

    primitive_id_type operand1_type, operand2_type;
    // printf("check term 1 IN\n");
    operand1_type = check_term((node->children)[0], type_exp_table, err_container, depth + 1, is_error);
    // printf("check term 1 OUT\n");
    if (*is_error)
    {
      return 0;
    }
    else
    {
      // printf("get rhs IN\n");
      operand2_type = get_assignment_rhs_type((node->children)[2], type_exp_table, err_container, depth + 1, is_error);
      // printf("get rhs OUT\n");
      if (*is_error)
      {
        return 0;
      }
    }

    terminal operator=((node->children)[1])->t;
    check_expression_compatibility(node, operand1_type, operand2_type, operator, err_container, is_error, depth);
    if (*is_error)
    {
      return 0;
    }
    else
    {
      // printf("Set expression start \n");
      char *expression = " ";
      char *blank = " ";
      expression = concat_strings((node->children)[0]->type_exp->prim_entry->lexeme, expression);
      expression = concat_strings(expression, ((node->children)[1])->token->lexeme);
      expression = concat_strings(expression, blank);
      expression = concat_strings(expression, (node->children)[2]->type_exp->prim_entry->lexeme);
      // printf("Set expression end \n");
      // printf("set non term IN\n");
      // printf("----------------------------Expression-------------------%s\n", expression);
      set_nonterminal_type_exp(node, operator== DIV ? real : operand1_type, expression);
      // printf("set non term OUT\n");
      return operator== DIV ? real : operand1_type;
    }
  }
}

void set_assignment_errors(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth)
{
  if (node->nt != assignStmt)
    assert(false, "[set_assignment_errors] invalid node passed");

  // assignStmt assignLhs EQUALS arithExpression SEMICOL

  bool is_error = false;
  primitive_id_type rhs_type = get_assignment_rhs_type((node->children)[2], type_exp_table, err_container, depth + 1, &is_error);

  if (is_error)
    return;

  is_error = false;
  primitive_id_type lhs_type = get_assignment_lhs_type((node->children)[0], type_exp_table, err_container, depth + 1, &is_error);
  if (is_error)
    return;

  if (lhs_type != rhs_type)
  {
    create_and_add_error(err_container, get_nt_line_num((node->children)[1]), depth, typeMismatch, assignStmt, ((node->children)[1])->token, NULL, NULL, NULL, NULL);
  }
  else
  {
    terminal operator= EQUALS;
    //TODO : LHS = RHS expression
  }
}