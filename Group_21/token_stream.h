/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "./entities.h"

#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

/*
	Token Stream is a linked list of token nodes
*/
typedef struct __TOKEN_STREAM__ token_stream;
struct __TOKEN_STREAM__
{
  token_node *head;
  token_node *tail;
};

token_stream *init_token_stream();

void add_to_token_stream(token_stream *ts, token_node *tn);

token_node *init_token_node(int line_num, char *lexeme, terminal token_name);

#endif