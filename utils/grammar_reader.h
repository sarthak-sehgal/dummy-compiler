/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdbool.h>
#include "../data_structures/grammar.h"
#include "../data_structures/hash_map.h"
#include "terminal_map.h"
#include "nonterminal_map.h"

#ifndef GRAMMAR_READER_H
#define GRAMMAR_READER_H

void read_grammar(char *file_name, grammar *G);

#endif