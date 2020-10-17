/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "general.h"

void assert(bool condition, char *error_string)
{
  if (!condition)
  {
    printf("ERROR: Assertion failed - %s\n", error_string);
    exit(1);
  }
}