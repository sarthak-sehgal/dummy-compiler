/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../lang_specs/entities.h"
#include "../utils/general.h"
#include "../utils/print.h"
#include "../utils/terminal_name.h"
#include "../utils/nonterminal_name.h"
#include "../data_structures/grammar.h"
#include "../data_structures/pda_stack.h"
#include "../data_structures/parse_tree.h"
#include "../data_structures/token_stream.h"

#ifndef PARSER_H
#define PARSER_H

void create_parse_tree(parse_tree_node *pt, grammar *G, token_stream *ts);

#endif