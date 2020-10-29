/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "grammar.h"

/*
  Creates a new grammar entity.
*/
grammar *init_grammar()
{
  grammar *G = (grammar *)calloc(1, sizeof(grammar));
  G->rules = (gm_prod_rule *)calloc(1, sizeof(gm_prod_rule));
  G->capacity = 1;
  G->curr_num = 0;

  return G;
}

/*
  Increase capacity of rule array when curr_num reaches the max capacity.
*/
void increase_capacity(grammar *G)
{
  assert(G->capacity == G->curr_num, "rule expansion called on correct condition");

  G->rules = realloc((void *)(G->rules), 2 * (G->capacity) * sizeof(gm_prod_rule));

  assert((G->rules) != NULL, "rule space expansion successful");

  G->capacity = G->capacity * 2;
}

/*
  Add new rule in the grammar rule array.
*/
void add_new_rule(grammar *G, nonterminal lhs, gm_node *rhs)
{
  if (G->curr_num == G->capacity)
  {
    increase_capacity(G);
  }

  assert(G->curr_num < G->capacity, "space sufficient in grammar for new rule");

  int curr_idx = G->curr_num;

  G->rules[curr_idx].lhs = lhs;

  if (rhs)
  {
    G->rules[curr_idx].rhs = (gm_node *)calloc(1, sizeof(gm_node));
  }
  gm_node *head = G->rules[curr_idx].rhs;
  gm_node *prev = NULL;

  while (rhs)
  {
    head->is_terminal = rhs->is_terminal;
    if (prev != NULL)
      head->prev = prev;
    if (rhs->is_terminal)
      head->gmt.t = rhs->gmt.t;
    else if (!rhs->is_terminal)
      head->gmt.nt = rhs->gmt.nt;
    if (rhs->next)
      head->next = (gm_node *)calloc(1, sizeof(gm_node));
    else
      head->next = NULL;
    prev = head;
    head = head->next;
    rhs = rhs->next;
  }

  G->curr_num += 1;
}

/*
  Set the start symbol for the grammar.
*/
void set_st_symbol(grammar *G, nonterminal nt)
{
  G->st_symbol = nt;
}