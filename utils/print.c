/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "print.h"

void print_rule(gm_prod_rule *rule)
{
  char *buffer = calloc(50, sizeof(char));
  get_nt_name(rule->lhs, buffer);
  printf("%s -> ", buffer);

  gm_node *head = rule->rhs;
  while (head)
  {
    if (head->is_terminal)
    {
      get_t_name(head->gmt.t, buffer);
      printf("%s ", buffer);
    }
    else
    {
      get_nt_name(head->gmt.nt, buffer);
      printf("%s ", buffer);
    }

    head = head->next;
  }

  free(buffer);
}

void print_grammar(grammar *G)
{
  char *buffer = calloc(100, sizeof(char));
  get_nt_name(G->st_symbol, buffer);
  printf("\n--- GRAMMAR ---\n\n Start symbol: %s", buffer);
  printf("\n\nRules (%d):\n", G->curr_num);
  for (int i = 0; i < G->curr_num; i++)
  {
    print_rule(&(G->rules[i]));
    printf("\n");
  }
  printf("\n---- END GRAMMAR ---\n");

  free(buffer);
}

void print_token_stream(token_stream *ts)
{
  if (!ts->head)
  {
    printf("Token stream is empty.\n");
    return;
  }
  else
  {
    printf("\n--- Begin Token Stream ---\n");
    token_node *node = ts->head;
    char *token_name = (char *)calloc(200, sizeof(char));
    while (node)
    {
      get_t_name(node->token_name, token_name);
      printf("(%d, %s, %s), ", node->line_num, node->lexeme, token_name);
      node = node->next;
    }

    printf("\n--- End Token Stream ---\n");
    free(token_name);
  }
}

void fancy_print_token_stream(token_stream *ts)
{
  if (!ts->head)
  {
    printf("Token stream is empty!\n");
    return;
  }
  else
  {
    printf("\n--- Begin Token Stream ---\n");
    int prev_line_num = 0;
    token_node *node = ts->head;
    char *token_name = (char *)calloc(200, sizeof(char));
    while (node)
    {
      if (node->line_num != prev_line_num)
      {
        printf("\n Line %d: ", node->line_num);
        prev_line_num = node->line_num;
      }
      get_t_name(node->token_name, token_name);
      printf("(%s, %s), ", node->lexeme, token_name);
      node = node->next;
    }

    printf("\n--- End Token Stream ---\n");
    free(token_name);
  }
}