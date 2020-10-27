/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../lang_specs/entities.h"
#include "../data_structures/hash_map.h"
#include "../data_structures/parse_tree.h"
#include "../data_structures/errors.h"
#include "../utils/nonterminal_name.h"
#include "../utils/terminal_name.h"

#ifndef TYPE_EXP_TABLE_H
#define TYPE_EXP_TABLE_H

hash_map *init_type_exp_table();

id_type get_id_type_from_dec_stmt_node(parse_tree_node *node);

void set_table_entry_for_prim_stmt(parse_tree_node *node, hash_map *type_exp_table);

void set_table_entry_for_arr_stmt(parse_tree_node *node, hash_map *type_exp_table);

void set_table_entry_for_jag_arr_stmt(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth);

void set_assignment_errors(parse_tree_node *node, hash_map *type_exp_table, error_container *err_container, int depth);

#endif