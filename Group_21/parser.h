/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "./entities.h"
#include "./general.h"
#include "./print.h"
#include "./terminal_name.h"
#include "./nonterminal_name.h"
#include "./grammar.h"
#include "./pda_stack.h"
#include "./parse_tree.h"
#include "./token_stream.h"
#include "./errors.h"
#include "./type_exp_table.h"

#ifndef PARSER_H
#define PARSER_H

void create_parse_tree(parse_tree_node **pt, grammar *G, token_stream *ts);

void set_declaration_types(parse_tree_node *root, hash_map *type_exp_table, error_container *err_container, int depth);

void traverse_parse_tree(parse_tree_node *tree_root, hash_map *type_exp_table, error_container *err_container);

#endif