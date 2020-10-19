/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "tokeniser.h"

/*
  Reading word by word possibilities:
    - Reserved keyword -> list, declare, R1, etc. => present in token_map
    - Special symbol and operators -> SQOP, SQCL, +, - etc => check manually
    - Number (NUM) => check manually
    - Identifiers

*/
void tokenise_source_code(char *file_name, token_stream *ts)
{
  FILE *fptr = fopen(file_name, "r");
  assert(fptr != NULL, "source code file opened successfully");

  hash_map *tok_map;
  tok_map = generate_token_map(15);

  char *buffer = calloc(300, sizeof(char));
  char *word = calloc(100, sizeof(char));
  int line_num = 0;

  while (fgets(buffer, 300, fptr))
  {
    // printf("%s\n", buffer);
    line_num++;

    if (buffer[0] == '\n' || buffer[0] == '\0')
      continue;

    int anchor = 0;
    for (int i = 0;; i++)
    {
      if (buffer[i] == ' ' || buffer[i] == '\n')
      {
        word[anchor] = '\0';
        if (anchor > 0)
        {
          token_node *token = init_token_node(line_num, word, 0);
          char c = word[0];
          int *keyword = find_in_map(tok_map, word);
          if (keyword != NULL)
          {
            token->token_name = *keyword;
          }
          else if (c >= '0' && c <= '9')
          {
            token->token_name = NUM;
          }
          else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
          {
            token->token_name = ID;
          }
          else
          {
            switch (c)
            {
            case '[':
              token->token_name = SQOP;
              break;
            case ']':
              token->token_name = SQCL;
              break;
            case '{':
              token->token_name = CURLOP;
              break;
            case '}':
              token->token_name = CURLCL;
              break;
            case '&':
              token->token_name = AND;
              break;
            case '|':
              token->token_name = OR;
              break;
            case '=':
              token->token_name = EQUALS;
              break;
            case '+':
              token->token_name = PLUS;
              break;
            case '-':
              token->token_name = MINUS;
              break;
            case '*':
              token->token_name = MUL;
              break;
            case '/':
              token->token_name = DIV;
              break;
            case ':':
              token->token_name = COLON;
              break;
            case ';':
              token->token_name = SEMICOL;
              break;
            case '.':
              token->token_name = ELIP;
              break;
            default:
              assert(false, "could not find token for the given source code!");
              break;
            }
          }

          add_to_token_stream(ts, token);
          free(token);
        }
        anchor = 0;
        if (buffer[i] == '\n')
          break;
        continue;
      }

      word[anchor++] = buffer[i];
    }
  }

  free(word);
  free(buffer);
}