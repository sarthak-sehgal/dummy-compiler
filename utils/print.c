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