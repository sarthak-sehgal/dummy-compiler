/*
  GROUP NO. 21
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
  elem->par_node = NULL;
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

  elem->prev = st->top;
  st->top = elem;
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
  top = NULL;
  st->size -= 1;
}

/*
  Delete the complete stack
*/
void delete_stack(pda_stack *st)
{
  while (st->size > 0)
    pop_from_stack(st);
  free(st);
  st = NULL;
}

/*
  Returns a copy of the stack
*/
pda_stack *copy_stack(pda_stack *st)
{
  pda_stack *new_st = init_stack();
  stack_elem *top = st->top;
  stack_elem *next = NULL;
  stack_elem *new_top = NULL;

  while (top)
  {
    stack_elem *el = init_stack_elem();
    if (new_top == NULL)
      new_top = el;
    if (next != NULL)
      next->prev = el;
    el->is_terminal = top->is_terminal;
    el->nt = top->nt;
    el->t = top->t;
    el->par_node = top->par_node;
    next = el;
    top = top->prev;
  }
  new_st->size = st->size;
  new_st->top = new_top;
  return new_st;
}