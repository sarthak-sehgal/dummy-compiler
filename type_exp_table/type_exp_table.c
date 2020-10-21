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

// void set_table_entries_for_prim_ids(parse_tree_node *node, hash_map *type_exp_table, primitive_id_type prim_type)
// {
//   if (node->is_terminal && node->t == ID)
//   {
//     primitive_id_entry *prim_entry = (primitive_id_entry *)calloc(1, sizeof(primitive_id_entry));
//     prim_entry->type = prim_type;
//     prim_entry->lexeme = node->lexeme;

//     type_exp_table_entry *entry = init_table_entry();
//     entry->type = primitive;
//     entry->prim_entry = prim_entry;
//     insert_into_map(type_exp_table, prim_entry->lexeme, entry);

//     return;
//   }

//   for (int i = 0; i < node->num_children; i++)
//     set_table_entries_for_prim_ids((node->children)[i], type_exp_table, prim_type);
// }

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

    (*id_list)[(*curr_stored)] = node->lexeme;
    *curr_stored += 1;
    return;
  }

  for (int i = 0; i < node->num_children; i++)
    get_lexeme_list_helper(id_list, (node->children)[i], curr_stored, capacity);
}

char **get_lexeme_list(parse_tree_node *node, int *num_id)
{
  int capacity = 1;
  char **id_list = (char **)calloc(1, sizeof(char *));
  for (int i = 0; i < node->num_children; i++)
  {
    parse_tree_node *child = (node->children)[i];
    if ((child->is_terminal && child->t == ID) || (child->is_terminal == false && child->nt == multipleIdList))
    {
      get_lexeme_list_helper(&id_list, child, num_id, &capacity);
    }
  }
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
    if (child->is_terminal == false && child->nt == primitiveDataType)
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