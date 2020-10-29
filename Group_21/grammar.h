/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "./entities.h"
#include "./general.h"

#ifndef GRAMMAR_H
#define GRAMMAR_H

/*
  Grammar is a struct having:
    - start symbol
    - array of rules
    - current count of rules
    - max count of rules (the current capacity of array)
*/
struct __GRAMMAR__
{
  nonterminal st_symbol;
  gm_prod_rule *rules;
  int curr_num;
  int capacity;
};
typedef struct __GRAMMAR__ grammar;

void set_st_symbol(grammar *G, nonterminal nt);

grammar *init_grammar();

void add_new_rule(grammar *G, nonterminal lhs, gm_node *rhs);

#endif