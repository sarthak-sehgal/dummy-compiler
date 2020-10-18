/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdbool.h>
#include "../data_structures/tokenStream.h"
#include "token_map.h"

#ifndef TOKENISER_H
#define TOKENISER_H

void tokeniseSourcecode(char *file_name, tokenStream *s);

#endif