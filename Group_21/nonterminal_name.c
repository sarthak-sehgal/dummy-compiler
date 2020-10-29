/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "nonterminal_name.h"

void get_nt_name(nonterminal t, char *name)
{
  switch (t)
  {
  case 0:
    strcpy(name, "module");
    break;
  case 1:
    strcpy(name, "decStmtGrp");
    break;
  case 2:
    strcpy(name, "assignStmtGrp");
    break;
  case 3:
    strcpy(name, "decStmt");
    break;
  case 4:
    strcpy(name, "assignStmt");
    break;
  case 5:
    strcpy(name, "primitiveDecStmt");
    break;
  case 6:
    strcpy(name, "jagArrDecStmt");
    break;
  case 7:
    strcpy(name, "primitiveDataType");
    break;
  case 8:
    strcpy(name, "multipleIdList");
    break;
  case 9:
    strcpy(name, "jagArrRange");
    break;
  case 10:
    strcpy(name, "jagArrInit");
    break;
  case 11:
    strcpy(name, "jagArrDimDec");
    break;
  case 12:
    strcpy(name, "jagArrValues");
    break;
  case 13:
    strcpy(name, "numList");
    break;
  case 14:
    strcpy(name, "idList");
    break;
  case 15:
    strcpy(name, "arrayRangeList");
    break;
  case 16:
    strcpy(name, "arrayRange");
    break;
  case 17:
    strcpy(name, "numOrId");
    break;
  case 18:
    strcpy(name, "numOrIdList");
    break;
  case 19:
    strcpy(name, "jagArrElement");
    break;
  case 20:
    strcpy(name, "arrayElement");
    break;
  case 21:
    strcpy(name, "operand");
    break;
  case 22:
    strcpy(name, "assignLhs");
    break;
  case 23:
    strcpy(name, "arithExpression");
    break;
  case 24:
    strcpy(name, "boolExpression");
    break;
  case 25:
    strcpy(name, "term");
    break;
  case 26:
    strcpy(name, "andExpression");
  case 27:
    strcpy(name, "arrayDecStmt");
    break;
  }
}