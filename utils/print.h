/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "../data_structures/grammar.h"
#include "../lang_specs/entities.h"
#include "../utils/nonterminal_name.h"
#include "../utils/terminal_name.h"
#include "../tokeniser/tokeniser.h"
#include "../data_structures/pda_stack.h"

#ifndef PRINT_H
#define PRINT_H

void print_grammar(grammar *G);

void print_rule(gm_prod_rule *rule);

void print_token_stream(token_stream *ts);

void fancy_print_token_stream(token_stream *ts);

void print_parse_tree(parse_tree_node *root);

void print_pda_stack(pda_stack *st);

#endif