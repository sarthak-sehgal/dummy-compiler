/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "grammar.h"

/*
  Creates a new grammar entity.
*/
grammar *generate_grammar()
{
  grammar *gm = (grammar *)calloc(1, sizeof(grammar));
  gm->rules = (gm_prod_rule *)calloc(1, sizeof(gm_prod_rule));
  gm->capacity = 1;
  gm->curr_num = 0;

  return gm;
}

/*
  Increase capacity of rule array when curr_num reaches the max capacity.
*/
void increase_capacity(grammar *gm)
{
  assert(gm->capacity == gm->curr_num, "rule expansion called on correct condition");

  gm->rules = realloc((void *)(gm->rules), 2 * (gm->capacity) * sizeof(gm_prod_rule));

  assert((gm->rules) != NULL, "rule space expansion successful");

  gm->capacity = gm->capacity * 2;
}

/*
  Add new rule in the grammar rule array.
*/
void add_new_rule(grammar *gm, nonterminal lhs, gm_node *rhs)
{
  if (gm->curr_num == gm->capacity)
  {
    increase_capacity(gm);
  }

  assert(gm->curr_num < gm->capacity, "space sufficient in grammar for new rule");

  int curr_idx = gm->curr_num;

  gm->rules[curr_idx].lhs = lhs;

  if (rhs)
  {
    gm->rules[curr_idx].rhs = (gm_node *)calloc(1, sizeof(gm_node));
  }
  gm_node *head = gm->rules[curr_idx].rhs;

  while (rhs)
  {
    head->is_terminal = rhs->is_terminal;
    if (rhs->is_terminal)
      head->gmt.t = rhs->gmt.t;
    else if (!rhs->is_terminal)
      head->gmt.nt = rhs->gmt.nt;
    if (rhs->next)
      head->next = (gm_node *)calloc(1, sizeof(gm_node));
    else
      head->next = NULL;
    head = head->next;
    rhs = rhs->next;
  }

  gm->curr_num += 1;
}

/*
  Set the start symbol for the grammar.
*/
void set_st_symbol(grammar *gm, nonterminal nt)
{
  gm->st_symbol = nt;
}