/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../utils/general.h"
#include "../lang_specs/entities.h"
#include "../data_structures/token_stream.h"
#include "../data_structures/hash_map.h"
#include "../utils/terminal_map.h"
#include "../utils/nonterminal_map.h"
#include "../utils/token_map.h"

#ifndef TOKENISER_H
#define TOKENISER_H

void tokenise_source_code(char *file_name, token_stream *ts);

#endif