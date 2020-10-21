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
    printf("\nERROR: Assertion failed - %s\n", error_string);
    exit(1);
  }
}

int string_to_num(char *string)
{
  int res = 0;
  for (int i = 0; string[i] != '\0'; i++)
  {
    char c = string[i];
    if (c < '0' || c > '9')
    {
      printf("\n[string_to_num] %s", string);
      assert(false, "[string_to_num] string contains invalid character");
    }
    res = res * 10 + c - '0';
  }

  return res;
}