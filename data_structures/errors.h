/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

#include "../lang_specs/entities.h"
#include "../utils/general.h"

#ifndef ERRORS_H
#define ERRORS_H

typedef enum error_type
{
  jagArrNumListOverflow,
  jagArrNumListUnderflow,
  jagArrIndexOutOfBounds,
  jagArrDecSizeUnderflow,
  jagArrNegativeRange,
  jagArr2dSizeMismatch,
  jagArr3dSizeMismatch,
  arrSizeMismatch,
  typeMismatch,
  invalidBoolOperation,
  invalidArithmeticOperation,
  invalidDivisionOperation,
  idNotArray,
  arrIndexOutOfBounds,
  invalidArrayIndexType,
  declarationInvalid
} error_type;

typedef struct error_elem
{
  int line_num;
  nonterminal statement_type;
  token_node *operation_token;
  token_node *operand1_token;
  token_node *operand2_token;
  char *operand1_lexeme;
  char *operand2_lexeme;
  int parse_tree_depth;
  error_type err_type;
} error_elem;

typedef struct error_container
{
  int curr_num;
  int capacity;
  error_elem **errors_arr;
} error_container;

error_container *init_error_container();

void add_error(error_container *container, error_elem *error);

void get_error_string(error_type err_type, char *buffer);

error_elem *init_error();

#endif