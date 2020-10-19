/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "token_stream.h"

/*
	Creates a new token stream entity.
*/
token_stream *init_token_stream()
{
  token_stream *ts = (token_stream *)calloc(1, sizeof(token_stream));
  ts->head = NULL;
  ts->tail = NULL;
  return ts;
}

/*
	Creates a new token node entity.
*/
token_node *init_token_node(int line_num, char *lexeme, terminal token_name)
{
  char *lexeme_copy = (char *)calloc(200, sizeof(char));
  int i = 0;
  for (; i < 200 && lexeme[i] != '\0'; i++)
  {
    lexeme_copy[i] = lexeme[i];
  }
  lexeme_copy[i] = '\0';

  token_node *node = (token_node *)calloc(1, sizeof(token_node));
  node->line_num = line_num;
  node->lexeme = lexeme_copy;
  node->token_name = token_name;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

/*
	Adds a token node to the tail of token stream.
  Creates a copy of the token so it can be deallocated safely.
*/
void add_to_token_stream(token_stream *ts, token_node *tn)
{
  token_node *copy_tn = init_token_node(tn->line_num, tn->lexeme, tn->token_name);
  if (ts->tail)
  {
    ts->tail->next = copy_tn;
    copy_tn->prev = ts->tail;
    ts->tail = copy_tn;
  }
  else
  {
    ts->head = copy_tn;
    ts->tail = copy_tn;
  }
}