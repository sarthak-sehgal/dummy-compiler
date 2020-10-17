/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdbool.h>
#include "../data_structures/grammar.h"
#include "../data_structures/hash_map.h"

#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H

grammar *grammar_parser(char *file_name, hash_map *tmap, hash_map *ntmap);

#endif