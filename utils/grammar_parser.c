/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "grammar_parser.h"

/*
  Parse grammar from the file.
*/
grammar *grammar_parser(char *file_name, hash_map *tmap, hash_map *ntmap)
{
  grammar *gm = generate_grammar();
  set_st_symbol(gm, module);

  char *buffer = calloc(300, sizeof(char));
  char *word = calloc(100, sizeof(char));

  FILE *fptr = fopen(file_name, "r");
  assert(fptr != NULL, "grammar file opened successfully");

  while (true)
  {

    if (fscanf(fptr, "%[^\n]\n", buffer) == EOF)
    {
      break;
    }
    int idx = 0;
    int t = 0;

    while (buffer[idx] != ' ')
    {
      word[t++] = buffer[idx++];
    }

    word[t] = '\0';

    int *curr_token = (int *)find_in_map(ntmap, word);

    if (curr_token == NULL)
    {
      assert(false, "lhs in grammar file not recognized");
    }
    else
    {
      nonterminal lhs = *curr_token;

      gm_node *dummy_node = (gm_node *)calloc(1, sizeof(gm_node));
      dummy_node->next = NULL;
      gm_node *prev_node = dummy_node;

      t = 0;
      while (buffer[idx] != '\0')
      {
        if (buffer[idx] == ' ')
        {
          t = 0;
          idx++;
          continue;
        }

        while (buffer[idx] != ' ' && buffer[idx] != '\0')
        {
          word[t++] = buffer[idx++];
        }

        word[t] = '\0';
        gm_node *curr_node = (gm_node *)calloc(1, sizeof(gm_node));
        curr_token = (int *)find_in_map(ntmap, word);
        if (curr_token == NULL)
        {
          curr_token = (int *)find_in_map(tmap, word);
          if (curr_token == NULL)
          {
            assert(false, "rhs symbol in grammar file not recognized");
          }
          else
          {
            curr_node->is_terminal = true;
            curr_node->gmt.t = *curr_token;
            curr_node->next = NULL;
            prev_node->next = curr_node;
            prev_node = curr_node;
          }
        }
        else
        {
          curr_node->is_terminal = false;
          curr_node->gmt.nt = *curr_token;
          curr_node->next = NULL;
          prev_node->next = curr_node;
          prev_node = curr_node;
        }
      }

      add_new_rule(gm, lhs, dummy_node->next);

      gm_node *node = dummy_node;
      gm_node *temp = node;
      while (node)
      {
        node = node->next;
        free(temp);
        temp = node;
      }
    }
  }

  free(buffer);
  return gm;
}