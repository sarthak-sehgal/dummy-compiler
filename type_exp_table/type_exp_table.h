/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../lang_specs/entities.h"
#include "../data_structures/hash_map.h"
#include "../data_structures/parse_tree.h"
#include "../utils/nonterminal_name.h"
#include "../utils/terminal_name.h"

#ifndef TYPE_EXP_TABLE_H
#define TYPE_EXP_TABLE_H

typedef enum id_type
{
  primitive,
  array,
  jag_array
} id_type;

typedef enum primitive_id_type
{
  integer,
  real,
  boolean
} primitive_id_type;

typedef struct __PRIMITIVE_ID_ENTRY__
{
  char *lexeme;
  primitive_id_type type;
  int value; // only valid if it is an integer
} primitive_id_entry;

typedef struct __ARRAY_ID_ENTRY__
{
  char *lexeme;
  bool is_static;
  int num_dimensions;
  int range_arr_capacity;
  token_node **range_start;
  token_node **range_end;
} array_id_entry;

typedef struct __JAGGED_ARR_ID_ENTRY__
{
  char *lexeme;
  int num_dimensions;
  int range_start;
  int range_end;
  int **sizes;
} jagged_arr_id_entry;

typedef struct __TYPE_EXP_TABLE_ENTRY__
{
  id_type type;
  union
  {
    primitive_id_entry *prim_entry;
    array_id_entry *arr_entry;
    jagged_arr_id_entry *jag_arr_entry;
  };
} type_exp_table_entry;

hash_map *init_type_exp_table();

id_type get_id_type_from_dec_stmt_node(parse_tree_node *node);

void set_table_entry_for_prim_stmt(parse_tree_node *node, hash_map *type_exp_table);

void set_table_entry_for_arr_stmt(parse_tree_node *node, hash_map *type_exp_table);

#endif