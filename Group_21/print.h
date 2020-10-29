/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "./grammar.h"
#include "./entities.h"
#include "./nonterminal_name.h"
#include "./terminal_name.h"
#include "./tokeniser.h"
#include "./pda_stack.h"
#include "./type_exp_table.h"
#include "./errors.h"

#ifndef PRINT_H
#define PRINT_H

void print_grammar(grammar *G);

void print_rule(gm_prod_rule *rule);

void print_token_stream(token_stream *ts);

void fancy_print_token_stream(token_stream *ts);

void print_parse_tree(parse_tree_node *root);

void print_parse_tree_symbols(parse_tree_node *root);

void print_pda_stack(pda_stack *st);

void print_type_exp_table(hash_map *type_exp_table);

void print_errors(error_container *err_container);

void print_invalid_vars(invalid_vars_struct *invalid_vars);

#endif