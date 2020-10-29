/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "./general.h"
#include "./entities.h"
#include "./token_stream.h"
#include "./hash_map.h"
#include "./terminal_map.h"
#include "./nonterminal_map.h"
#include "./token_map.h"

#ifndef TOKENISER_H
#define TOKENISER_H

void tokenise_source_code(char *file_name, token_stream *ts);

#endif