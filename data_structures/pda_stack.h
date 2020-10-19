/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../lang_specs/entities.h"
#include "../utils/general.h"

#ifndef PDA_STACK_H
#define PDA_STACK_H

/*
  PDA stack element contains:
    - info about whether it is a terminal or nonterminal
    - the terminal/nonterminal enum
    - pointer to previous element
*/
typedef struct __STACK_ELEM__ stack_elem;
struct __STACK_ELEM__
{
  bool is_terminal;
  union
  {
    terminal t;
    nonterminal nt;
  };
  stack_elem *prev;
};

/*
	Data structure for the PDA stack.
*/
struct __PDA_STACK__
{
  int size;
  stack_elem *top;
};
typedef struct __PDA_STACK__ pda_stack;

stack_elem *init_stack_elem();

pda_stack *init_stack();

void push_to_stack(pda_stack *st, stack_elem *elem);

void pop_from_stack(pda_stack *st);

#endif