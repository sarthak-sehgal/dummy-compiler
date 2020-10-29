/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "nonterminal_map.h"

hash_map *generate_nt_map(int map_size)
{
  hash_map *map = init_map(map_size);
  int *temp;

  temp = calloc(1, sizeof(int));
  *temp = 0;
  insert_into_map(map, "module", temp);

  temp = calloc(1, sizeof(int));
  *temp = 1;
  insert_into_map(map, "decStmtGrp", temp);

  temp = calloc(1, sizeof(int));
  *temp = 2;
  insert_into_map(map, "assignStmtGrp", temp);

  temp = calloc(1, sizeof(int));
  *temp = 3;
  insert_into_map(map, "decStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 4;
  insert_into_map(map, "assignStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 5;
  insert_into_map(map, "primitiveDecStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 6;
  insert_into_map(map, "jagArrDecStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 7;
  insert_into_map(map, "primitiveDataType", temp);

  temp = calloc(1, sizeof(int));
  *temp = 8;
  insert_into_map(map, "multipleIdList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 9;
  insert_into_map(map, "jagArrRange", temp);

  temp = calloc(1, sizeof(int));
  *temp = 10;
  insert_into_map(map, "jagArrInit", temp);

  temp = calloc(1, sizeof(int));
  *temp = 11;
  insert_into_map(map, "jagArrDimDec", temp);

  temp = calloc(1, sizeof(int));
  *temp = 12;
  insert_into_map(map, "jagArrValues", temp);

  temp = calloc(1, sizeof(int));
  *temp = 13;
  insert_into_map(map, "numList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 14;
  insert_into_map(map, "idList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 15;
  insert_into_map(map, "arrayRangeList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 16;
  insert_into_map(map, "arrayRange", temp);

  temp = calloc(1, sizeof(int));
  *temp = 17;
  insert_into_map(map, "numOrId", temp);

  temp = calloc(1, sizeof(int));
  *temp = 18;
  insert_into_map(map, "numOrIdList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 19;
  insert_into_map(map, "jagArrElement", temp);

  temp = calloc(1, sizeof(int));
  *temp = 20;
  insert_into_map(map, "arrayElement", temp);

  temp = calloc(1, sizeof(int));
  *temp = 21;
  insert_into_map(map, "operand", temp);

  temp = calloc(1, sizeof(int));
  *temp = 22;
  insert_into_map(map, "assignLhs", temp);

  temp = calloc(1, sizeof(int));
  *temp = 23;
  insert_into_map(map, "arithExpression", temp);

  temp = calloc(1, sizeof(int));
  *temp = 24;
  insert_into_map(map, "boolExpression", temp);

  temp = calloc(1, sizeof(int));
  *temp = 25;
  insert_into_map(map, "term", temp);

  temp = calloc(1, sizeof(int));
  *temp = 26;
  insert_into_map(map, "andExpression", temp);

  temp = calloc(1, sizeof(int));
  *temp = 27;
  insert_into_map(map, "arrayDecStmt", temp);

  temp = NULL;
  return map;
}