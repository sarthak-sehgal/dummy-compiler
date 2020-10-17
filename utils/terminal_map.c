/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "terminal_map.h"

hash_map *generate_t_map(int map_size)
{
  // TO DO: change the non terminals here as per the enum list in entities.h
  hash_map *map = init_map(map_size);
  int *temp;

  temp = calloc(1, sizeof(int));
  *temp = 0;
  insert_into_map(map, "DECLARE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 1;
  insert_into_map(map, "MODULE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 2;
  insert_into_map(map, "ID", temp);

  temp = calloc(1, sizeof(int));
  *temp = 3;
  insert_into_map(map, "SEMICOL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 4;
  insert_into_map(map, "DRIVERDEF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 5;
  insert_into_map(map, "DRIVER", temp);

  temp = calloc(1, sizeof(int));
  *temp = 6;
  insert_into_map(map, "PROGRAM", temp);

  temp = calloc(1, sizeof(int));
  *temp = 7;
  insert_into_map(map, "DRIVERENDDEF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 8;
  insert_into_map(map, "DEF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 9;
  insert_into_map(map, "ENDDEF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 10;
  insert_into_map(map, "TAKES", temp);

  temp = calloc(1, sizeof(int));
  *temp = 11;
  insert_into_map(map, "INPUT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 12;
  insert_into_map(map, "SQBO", temp);

  temp = calloc(1, sizeof(int));
  *temp = 13;
  insert_into_map(map, "SQBC", temp);

  temp = calloc(1, sizeof(int));
  *temp = 14;
  insert_into_map(map, "RETURNS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 15;
  insert_into_map(map, "COLON", temp);

  temp = calloc(1, sizeof(int));
  *temp = 16;
  insert_into_map(map, "COMMA", temp);

  temp = calloc(1, sizeof(int));
  *temp = 17;
  insert_into_map(map, "INTEGER", temp);

  temp = calloc(1, sizeof(int));
  *temp = 18;
  insert_into_map(map, "REAL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 19;
  insert_into_map(map, "BOOLEAN", temp);

  temp = calloc(1, sizeof(int));
  *temp = 20;
  insert_into_map(map, "ARRAY", temp);

  temp = calloc(1, sizeof(int));
  *temp = 21;
  insert_into_map(map, "OF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 22;
  insert_into_map(map, "RANGEOP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 23;
  insert_into_map(map, "START", temp);

  temp = calloc(1, sizeof(int));
  *temp = 24;
  insert_into_map(map, "END", temp);

  temp = calloc(1, sizeof(int));
  *temp = 25;
  insert_into_map(map, "BO", temp);

  temp = calloc(1, sizeof(int));
  *temp = 26;
  insert_into_map(map, "BC", temp);

  temp = calloc(1, sizeof(int));
  *temp = 27;
  insert_into_map(map, "GET_VALUE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 28;
  insert_into_map(map, "PRINT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 29;
  insert_into_map(map, "TRUE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 30;
  insert_into_map(map, "FALSE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 31;
  insert_into_map(map, "NUM", temp);

  temp = calloc(1, sizeof(int));
  *temp = 32;
  insert_into_map(map, "RNUM", temp);

  temp = calloc(1, sizeof(int));
  *temp = 33;
  insert_into_map(map, "ASSIGNOP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 34;
  insert_into_map(map, "USE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 35;
  insert_into_map(map, "WITH", temp);

  temp = calloc(1, sizeof(int));
  *temp = 36;
  insert_into_map(map, "PARAMETERS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 37;
  insert_into_map(map, "PLUS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 38;
  insert_into_map(map, "MINUS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 39;
  insert_into_map(map, "MUL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 40;
  insert_into_map(map, "DIV", temp);

  temp = calloc(1, sizeof(int));
  *temp = 41;
  insert_into_map(map, "AND", temp);

  temp = calloc(1, sizeof(int));
  *temp = 42;
  insert_into_map(map, "OR", temp);

  temp = calloc(1, sizeof(int));
  *temp = 43;
  insert_into_map(map, "LT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 44;
  insert_into_map(map, "LE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 45;
  insert_into_map(map, "GT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 46;
  insert_into_map(map, "GE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 47;
  insert_into_map(map, "EQ", temp);

  temp = calloc(1, sizeof(int));
  *temp = 48;
  insert_into_map(map, "NE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 49;
  insert_into_map(map, "SWITCH", temp);

  temp = calloc(1, sizeof(int));
  *temp = 50;
  insert_into_map(map, "CASE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 51;
  insert_into_map(map, "BREAK", temp);

  temp = calloc(1, sizeof(int));
  *temp = 52;
  insert_into_map(map, "DEFAULT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 53;
  insert_into_map(map, "FOR", temp);

  temp = calloc(1, sizeof(int));
  *temp = 54;
  insert_into_map(map, "IN", temp);

  temp = calloc(1, sizeof(int));
  *temp = 55;
  insert_into_map(map, "WHILE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 56;
  insert_into_map(map, "EPS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 57;
  insert_into_map(map, "DOLLAR", temp);

  temp = NULL;
  return map;
}