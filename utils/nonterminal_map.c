/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "nonterminal_map.h"

hash_map *generate_nt_map(int map_size)
{
  // TO DO: change the non terminals here as per the enum list in entities.h
  hash_map *map = init_map(map_size);
  int *temp;

  temp = calloc(1, sizeof(int));
  *temp = 0;
  insert_into_map(map, "program", temp);

  temp = calloc(1, sizeof(int));
  *temp = 1;
  insert_into_map(map, "moduleDeclarations", temp);

  temp = calloc(1, sizeof(int));
  *temp = 2;
  insert_into_map(map, "otherModules", temp);

  temp = calloc(1, sizeof(int));
  *temp = 3;
  insert_into_map(map, "driverModule", temp);

  temp = calloc(1, sizeof(int));
  *temp = 4;
  insert_into_map(map, "otherModule", temp);

  temp = calloc(1, sizeof(int));
  *temp = 5;
  insert_into_map(map, "moduleDeclaration", temp);

  temp = calloc(1, sizeof(int));
  *temp = 6;
  insert_into_map(map, "module", temp);

  temp = calloc(1, sizeof(int));
  *temp = 7;
  insert_into_map(map, "moduleDef", temp);

  temp = calloc(1, sizeof(int));
  *temp = 8;
  insert_into_map(map, "input_plist", temp);

  temp = calloc(1, sizeof(int));
  *temp = 9;
  insert_into_map(map, "ret", temp);

  temp = calloc(1, sizeof(int));
  *temp = 10;
  insert_into_map(map, "output_plist", temp);

  temp = calloc(1, sizeof(int));
  *temp = 11;
  insert_into_map(map, "dataType", temp);

  temp = calloc(1, sizeof(int));
  *temp = 12;
  insert_into_map(map, "input_plist2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 13;
  insert_into_map(map, "type", temp);

  temp = calloc(1, sizeof(int));
  *temp = 14;
  insert_into_map(map, "output_plist2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 15;
  insert_into_map(map, "range_arrays", temp);

  temp = calloc(1, sizeof(int));
  *temp = 16;
  insert_into_map(map, "index_nt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 17;
  insert_into_map(map, "statements", temp);

  temp = calloc(1, sizeof(int));
  *temp = 18;
  insert_into_map(map, "statement", temp);

  temp = calloc(1, sizeof(int));
  *temp = 19;
  insert_into_map(map, "ioStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 20;
  insert_into_map(map, "simpleStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 21;
  insert_into_map(map, "declareStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 22;
  insert_into_map(map, "condionalStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 23;
  insert_into_map(map, "iterativeStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 24;
  insert_into_map(map, "var", temp);

  temp = calloc(1, sizeof(int));
  *temp = 25;
  insert_into_map(map, "boolConstt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 26;
  insert_into_map(map, "var_id_num", temp);

  temp = calloc(1, sizeof(int));
  *temp = 27;
  insert_into_map(map, "whichId", temp);

  temp = calloc(1, sizeof(int));
  *temp = 28;
  insert_into_map(map, "assignmentStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 29;
  insert_into_map(map, "moduleReuseStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 30;
  insert_into_map(map, "whichStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 31;
  insert_into_map(map, "lvalueIDStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 32;
  insert_into_map(map, "lvalueARRStmt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 33;
  insert_into_map(map, "expression", temp);

  temp = calloc(1, sizeof(int));
  *temp = 34;
  insert_into_map(map, "optional", temp);

  temp = calloc(1, sizeof(int));
  *temp = 35;
  insert_into_map(map, "idList", temp);

  temp = calloc(1, sizeof(int));
  *temp = 36;
  insert_into_map(map, "idList2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 37;
  insert_into_map(map, "arithmeticOrBooleanExpr", temp);

  temp = calloc(1, sizeof(int));
  *temp = 38;
  insert_into_map(map, "unary_nt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 39;
  insert_into_map(map, "unary_op", temp);

  temp = calloc(1, sizeof(int));
  *temp = 40;
  insert_into_map(map, "new_NT", temp);

  temp = calloc(1, sizeof(int));
  *temp = 41;
  insert_into_map(map, "arithmeticExpr", temp);

  temp = calloc(1, sizeof(int));
  *temp = 42;
  insert_into_map(map, "AnyTerm", temp);

  temp = calloc(1, sizeof(int));
  *temp = 43;
  insert_into_map(map, "arithmeticOrBooleanExpr2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 44;
  insert_into_map(map, "logicalOp", temp);

  temp = calloc(1, sizeof(int));
  *temp = 45;
  insert_into_map(map, "AnyTerm2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 46;
  insert_into_map(map, "relationalOp", temp);

  temp = calloc(1, sizeof(int));
  *temp = 47;
  insert_into_map(map, "term", temp);

  temp = calloc(1, sizeof(int));
  *temp = 48;
  insert_into_map(map, "arithmeticExpr2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 49;
  insert_into_map(map, "op1", temp);

  temp = calloc(1, sizeof(int));
  *temp = 50;
  insert_into_map(map, "factor", temp);

  temp = calloc(1, sizeof(int));
  *temp = 51;
  insert_into_map(map, "term2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 52;
  insert_into_map(map, "op2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 53;
  insert_into_map(map, "caseStmts", temp);

  temp = calloc(1, sizeof(int));
  *temp = 54;
  insert_into_map(map, "default_nt", temp);

  temp = calloc(1, sizeof(int));
  *temp = 55;
  insert_into_map(map, "value", temp);

  temp = calloc(1, sizeof(int));
  *temp = 56;
  insert_into_map(map, "caseStmts2", temp);

  temp = calloc(1, sizeof(int));
  *temp = 57;
  insert_into_map(map, "range", temp);

  temp = NULL;
  return map;
}