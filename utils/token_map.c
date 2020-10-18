/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "terminal_map.h"

hash_map *generate_token_map(int map_size)
{
  hash_map *map = init_map(map_size);
  int *temp;

  temp = calloc(1, sizeof(int));
  *temp = 0;
  insert_into_map(map, "declare", temp);

  temp = calloc(1, sizeof(int));
  *temp = 4;
  insert_into_map(map, "list", temp);

  temp = calloc(1, sizeof(int));
  *temp = 5;
  insert_into_map(map, "of", temp);

  temp = calloc(1, sizeof(int));
  *temp = 6;
  insert_into_map(map, "variables", temp);

  temp = calloc(1, sizeof(int));
  *temp = 7;
  insert_into_map(map, "jagged", temp);

  temp = calloc(1, sizeof(int));
  *temp = 8;
  insert_into_map(map, "array", temp);

  temp = calloc(1, sizeof(int));
  *temp = 9;
  insert_into_map(map, "integer", temp);

  temp = calloc(1, sizeof(int));
  *temp = 10;
  insert_into_map(map, "R1", temp);

  temp = calloc(1, sizeof(int));
  *temp = 14;
  insert_into_map(map, "size", temp);

  temp = calloc(1, sizeof(int));
  *temp = 15;
  insert_into_map(map, "values", temp);

  temp = calloc(1, sizeof(int));
  *temp = 19;
  insert_into_map(map, "real", temp);

  temp = calloc(1, sizeof(int));
  *temp = 20;
  insert_into_map(map, "boolean", temp);

  temp = NULL;
  return map;
}