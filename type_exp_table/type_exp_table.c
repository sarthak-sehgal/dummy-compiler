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

void get_arr_range_info(array_id_entry *dummy_array_entry, parse_tree_node *node)
{
  if (node->nt == arrayRange)
  {
    if (dummy_array_entry->num_dimensions == dummy_array_entry->range_arr_capacity)
    {
      // reallocate
      dummy_array_entry->range_arr_capacity *= 2;
      dummy_array_entry->range_start = (token_node **)realloc(dummy_array_entry->range_start, sizeof(token_node *) * (dummy_array_entry->range_arr_capacity));
      dummy_array_entry->range_end = (token_node **)realloc(dummy_array_entry->range_end, sizeof(token_node *) * (dummy_array_entry->range_arr_capacity));
    }
    if (node->num_children < 4)
      assert(false, "[get_arr_range_info] arrayRange node has insufficient children");
    parse_tree_node *range_st_dim = (((node->children)[1])->children)[0]; // arrayRange->children[1] points to numOrId and then its first child points to NUM or ID
    parse_tree_node *range_en_dim = (((node->children)[3])->children)[0]; // arrayRange->children[3] points to numOrId and then its first child points to NUM or ID
    if (range_st_dim->t == ID || range_en_dim->t == ID)
      dummy_array_entry->is_static = false;
    (dummy_array_entry->range_start)[dummy_array_entry->num_dimensions] = range_st_dim->token;
    (dummy_array_entry->range_end)[dummy_array_entry->num_dimensions] = range_en_dim->token;

    dummy_array_entry->num_dimensions += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if (child->nt == arrayRangeList || child->nt == arrayRange)
      get_arr_range_info(dummy_array_entry, child);
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