/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <string.h>

#include "errors.h"

error_container *init_error_container()
{
  error_container *container = (error_container *)calloc(1, sizeof(error_container));
  container->capacity = 5;
  container->curr_num = 0;
  container->errors_arr = (error_elem **)calloc(container->capacity, sizeof(error_elem *));

  return container;
}

void add_error(error_container *container, error_elem *error)
{
  if (container->curr_num == container->capacity)
  {
    // reallocate
    container->capacity *= 2;
    container->errors_arr = (error_elem **)realloc(container->errors_arr, (container->capacity) * sizeof(error_elem *));
    if (container->errors_arr == NULL)
      assert(false, "[add_error] not enough memory to store errors!");
  }

  (container->errors_arr)[container->curr_num] = error;
  container->curr_num += 1;
}

void get_error_string(error_type err_type, char *buffer)
{
  switch (err_type)
  {
  case jagArrNumListOverflow:
    strcpy(buffer, "JA num list overflow");
    break;
  case jagArrNumListUnderflow:
    strcpy(buffer, "JA num list empty");
    break;
  case jagArrIndexOutOfBounds:
    strcpy(buffer, "JA index out of bounds");
    break;
  case jagArrDecSizeUnderflow:
    strcpy(buffer, "JA size underflow");
    break;
  case jagArrNegativeRange:
    strcpy(buffer, "JA invalid range");
    break;
  case jagArr2dSizeMismatch:
    strcpy(buffer, "JA 2D size mismatch");
    break;
  case jagArr3dSizeMismatch:
    strcpy(buffer, "JA 3D size mismatch");
    break;
  case arrSizeMismatch:
    strcpy(buffer, "Array size mismatch");
    break;
  case typeMismatch:
    strcpy(buffer, "Data type mismatch");
    break;
  case invalidBoolOperation:
    strcpy(buffer, "Invalid operator for boolean operands");
    break;
  case invalidArithmeticOperation:
    strcpy(buffer, "Invalid operator for arithmetic operands");
    break;
  case invalidDivisionOperation:
    strcpy(buffer, "Invalid operands for division");
  case idNotArray:
    strcpy(buffer, "Identifier not array");
    break;
  case arrIndexOutOfBounds:
    strcpy(buffer, "Array index out of bounds");
    break;
  case invalidArrayIndexType:
    strcpy(buffer, "Invalid array index type");
    break;
  case declarationInvalid:
    strcpy(buffer, "Declaration of identifier invalid");
    break;
  default:
    assert(false, "[get_error_string] error type not identified!");
    break;
  }
}

error_elem *init_error()
{
  error_elem *error = calloc(1, sizeof(error_elem));
  error->line_num = -1;
  error->err_type = 0;
  error->operand1_token = NULL;
  error->operand2_token = NULL;
  error->operation_token = NULL;
  error->parse_tree_depth = -1;
  error->statement_type = decStmt;
  return error;
}