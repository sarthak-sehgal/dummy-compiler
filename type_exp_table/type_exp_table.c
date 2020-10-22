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

    type_exp_table_entry *entry = init_table_entry();
    entry->type = primitive;
    entry->prim_entry = prim_entry;
    insert_into_map(type_exp_table, prim_entry->lexeme, entry);
  }
  free(id_list);
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

    type_exp_table_entry *entry = init_table_entry();
    entry->type = array;
    entry->arr_entry = array_entry;
    insert_into_map(type_exp_table, id_list[i], entry);
  }
  free(id_list);
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
    printf("\nrange node error %d", range_node->num_children);
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

void set_jag_arr_value_sizes(parse_tree_node *node, jagged_arr_id_entry *jag_arr_entry, int *values_cnt, int max_val_count, int sizes_idx, int depth, error_container *err_container)
{
  if (node->nt == numList)
  {
    if ((*values_cnt) >= max_val_count)
    {
      error_elem *error = init_error();
      error->err_type = jagArrNumListOverflow;
      error->line_num = get_nt_line_num(node);
      error->parse_tree_depth = depth;
      error->statement_type = decStmt;
      add_error(err_container, error);
      return;
    }

    int num_count = get_num_count(node);
    if (num_count == 0)
    {
      error_elem *error = init_error();
      error->err_type = jagArrNumListUnderflow;
      error->line_num = get_nt_line_num(node);
      error->parse_tree_depth = depth;
      error->statement_type = decStmt;
      add_error(err_container, error);
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
    if (node->num_children < 11)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec");

    parse_tree_node *idx_node = (node->children)[2];
    if (idx_node->t != NUM)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec: index node not 2nd child");
    int idx = string_to_num(idx_node->token->lexeme);
    if (idx < jag_arr_entry->range_start || idx > jag_arr_entry->range_end)
    {
      error_elem *error = init_error();
      error->err_type = jagArrIndexOutOfBounds;
      error->line_num = idx_node->token->line_num;
      error->parse_tree_depth = depth;
      error->statement_type = decStmt;
      add_error(err_container, error);
      return;
    }

    parse_tree_node *size_node = (node->children)[6];
    if (size_node->t != NUM)
      assert(false, "[set_jag_arr_sizes] corrupt node jagArrDimDec: size node not 6th child");
    int size = string_to_num(size_node->token->lexeme);
    if (size <= 0)
    {
      error_elem *error = init_error();
      error->err_type = jagArrDecSizeUnderflow;
      error->line_num = size_node->token->line_num;
      error->parse_tree_depth = depth;
      error->statement_type = decStmt;
      add_error(err_container, error);
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

  jagged_arr_id_entry dummy_jag_arr_entry;
  set_jag_arr_dim_and_range(node, &dummy_jag_arr_entry);

  int range_start = dummy_jag_arr_entry.range_start;
  int range_end = dummy_jag_arr_entry.range_end;
  if (range_end < range_start)
  {
    error_elem *error = init_error();
    error->statement_type = decStmt;
    error->err_type = jagArrNegativeRange;
    error->line_num = get_nt_line_num(node);
    error->parse_tree_depth = depth;
    add_error(err_container, error);
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
    return;
  }

  // get list of identifiers
  int num_id = 0;
  char **id_list = get_lexeme_list(node, &num_id);
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

    type_exp_table_entry *entry = init_table_entry();
    entry->type = jag_array;
    entry->jag_arr_entry = jag_array_entry;
    insert_into_map(type_exp_table, id_list[i], entry);
  }
  free(id_list);
}