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

#ifndef PRINT_H
#define PRINT_H

void print_grammar(grammar *G);

void print_token_stream(token_stream *ts);

void fancy_print_token_stream(token_stream *ts);

#endif