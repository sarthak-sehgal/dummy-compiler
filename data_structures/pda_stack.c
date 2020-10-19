/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "pda_stack.h"

/*
  Allocate memory to stack element
*/
stack_elem *init_stack_elem()
{
  stack_elem *elem = (stack_elem *)calloc(1, sizeof(stack_elem));
  elem->is_terminal = true;
  elem->t = EPS;
  elem->prev = NULL;
  return elem;
}

/*
  Allocate memory to stack
*/
pda_stack *init_stack()
{
  pda_stack *st = (pda_stack *)calloc(1, sizeof(pda_stack));
  st->top = NULL;
  st->size = 0;
  return st;
}

/*
  Push a stack element to the stack (LIFO operation)
*/
void push_to_stack(pda_stack *st, stack_elem *elem)
{
  if (elem == NULL)
    return;
  if (st == NULL)
    assert(false, "cannot push when stack is not defined!");

  stack_elem *elem_copy = init_stack_elem();
  elem_copy->is_terminal = elem->is_terminal;
  elem_copy->nt = elem->nt;
  elem_copy->t = elem->t;

  elem_copy->prev = st->top;
  st->top = elem_copy;
  st->size += 1;
}

/*
  Pop a stack element from top of the stack (LIFO operation).
  Throws error if stack is empty.
*/
void pop_from_stack(pda_stack *st)
{
  if (st == NULL)
    assert(false, "cannot pop when stack is not defined!");
  if (st->top == NULL)
    assert(false, "cannot pop when stack is empty!");

  stack_elem *top = st->top;
  st->top = st->top->prev;
  free(top);
  st->size -= 1;
}
