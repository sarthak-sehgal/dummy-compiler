/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "terminal_map.h"

hash_map *generate_t_map(int map_size)
{
  hash_map *map = init_map(map_size);
  int *temp;

  temp = calloc(1, sizeof(int));
  *temp = 0;
  insert_into_map(map, "DECLARE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 1;
  insert_into_map(map, "ID", temp);

  temp = calloc(1, sizeof(int));
  *temp = 2;
  insert_into_map(map, "COLON", temp);

  temp = calloc(1, sizeof(int));
  *temp = 3;
  insert_into_map(map, "SEMICOL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 4;
  insert_into_map(map, "LIST", temp);

  temp = calloc(1, sizeof(int));
  *temp = 5;
  insert_into_map(map, "OF", temp);

  temp = calloc(1, sizeof(int));
  *temp = 6;
  insert_into_map(map, "VARIABLES", temp);

  temp = calloc(1, sizeof(int));
  *temp = 7;
  insert_into_map(map, "JAGGED", temp);

  temp = calloc(1, sizeof(int));
  *temp = 8;
  insert_into_map(map, "ARRAY", temp);

  temp = calloc(1, sizeof(int));
  *temp = 9;
  insert_into_map(map, "INTEGER", temp);

  temp = calloc(1, sizeof(int));
  *temp = 10;
  insert_into_map(map, "R1", temp);

  temp = calloc(1, sizeof(int));
  *temp = 11;
  insert_into_map(map, "SQOP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 12;
  insert_into_map(map, "NUM", temp);

  temp = calloc(1, sizeof(int));
  *temp = 13;
  insert_into_map(map, "SQCL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 14;
  insert_into_map(map, "SIZE", temp);

  temp = calloc(1, sizeof(int));
  *temp = 15;
  insert_into_map(map, "VALUES", temp);

  temp = calloc(1, sizeof(int));
  *temp = 16;
  insert_into_map(map, "CURLOP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 17;
  insert_into_map(map, "CURLCL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 18;
  insert_into_map(map, "EPS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 19;
  insert_into_map(map, "REAL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 20;
  insert_into_map(map, "BOOLEAN", temp);

  temp = calloc(1, sizeof(int));
  *temp = 21;
  insert_into_map(map, "ELIP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 22;
  insert_into_map(map, "EQUALS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 23;
  insert_into_map(map, "PLUS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 24;
  insert_into_map(map, "MINUS", temp);

  temp = calloc(1, sizeof(int));
  *temp = 25;
  insert_into_map(map, "MUL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 26;
  insert_into_map(map, "DIV", temp);

  temp = calloc(1, sizeof(int));
  *temp = 27;
  insert_into_map(map, "OR", temp);

  temp = calloc(1, sizeof(int));
  *temp = 28;
  insert_into_map(map, "AND", temp);

  temp = calloc(1, sizeof(int));
  *temp = 29;
  insert_into_map(map, "PROGRAM", temp);

  temp = calloc(1, sizeof(int));
  *temp = 30;
  insert_into_map(map, "BROP", temp);

  temp = calloc(1, sizeof(int));
  *temp = 31;
  insert_into_map(map, "BRCL", temp);

  temp = calloc(1, sizeof(int));
  *temp = 32;
  insert_into_map(map, "COMMA", temp);

  temp = NULL;
  return map;
}