/*
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
    strcpy(name, "program");
    break;
  case 1:
    strcpy(name, "moduleDeclarations");
    break;
  case 2:
    strcpy(name, "otherModules");
    break;
  case 3:
    strcpy(name, "driverModule");
    break;
  case 4:
    strcpy(name, "otherModule");
    break;
  case 5:
    strcpy(name, "moduleDeclaration");
    break;
  case 6:
    strcpy(name, "module");
    break;
  case 7:
    strcpy(name, "moduleDef");
    break;
  case 8:
    strcpy(name, "input_plist");
    break;
  case 9:
    strcpy(name, "ret");
    break;
  case 10:
    strcpy(name, "output_plist");
    break;
  case 11:
    strcpy(name, "dataType");
    break;
  case 12:
    strcpy(name, "input_plist2");
    break;
  case 13:
    strcpy(name, "type");
    break;
  case 14:
    strcpy(name, "output_plist2");
    break;
  case 15:
    strcpy(name, "range_arrays");
    break;
  case 16:
    strcpy(name, "index_nt");
    break;
  case 17:
    strcpy(name, "statements");
    break;
  case 18:
    strcpy(name, "statement");
    break;
  case 19:
    strcpy(name, "ioStmt");
    break;
  case 20:
    strcpy(name, "simpleStmt");
    break;
  case 21:
    strcpy(name, "declareStmt");
    break;
  case 22:
    strcpy(name, "condionalStmt");
    break;
  case 23:
    strcpy(name, "iterativeStmt");
    break;
  case 24:
    strcpy(name, "var");
    break;
  case 25:
    strcpy(name, "boolConstt");
    break;
  case 26:
    strcpy(name, "var_id_num");
    break;
  case 27:
    strcpy(name, "whichId");
    break;
  case 28:
    strcpy(name, "assignmentStmt");
    break;
  case 29:
    strcpy(name, "moduleReuseStmt");
    break;
  case 30:
    strcpy(name, "whichStmt");
    break;
  case 31:
    strcpy(name, "lvalueIDStmt");
    break;
  case 32:
    strcpy(name, "lvalueARRStmt");
    break;
  case 33:
    strcpy(name, "expression");
    break;
  case 34:
    strcpy(name, "optional");
    break;
  case 35:
    strcpy(name, "idList");
    break;
  case 36:
    strcpy(name, "idList2");
    break;
  case 37:
    strcpy(name, "arithmeticOrBooleanExpr");
    break;
  case 38:
    strcpy(name, "unary_nt");
    break;
  case 39:
    strcpy(name, "unary_op");
    break;
  case 40:
    strcpy(name, "new_NT");
    break;
  case 41:
    strcpy(name, "arithmeticExpr");
    break;
  case 42:
    strcpy(name, "AnyTerm");
    break;
  case 43:
    strcpy(name, "arithmeticOrBooleanExpr2");
    break;
  case 44:
    strcpy(name, "logicalOp");
    break;
  case 45:
    strcpy(name, "AnyTerm2");
    break;
  case 46:
    strcpy(name, "relationalOp");
    break;
  case 47:
    strcpy(name, "term");
    break;
  case 48:
    strcpy(name, "arithmeticExpr2");
    break;
  case 49:
    strcpy(name, "op1");
    break;
  case 50:
    strcpy(name, "factor");
    break;
  case 51:
    strcpy(name, "term2");
    break;
  case 52:
    strcpy(name, "op2");
    break;
  case 53:
    strcpy(name, "caseStmts");
    break;
  case 54:
    strcpy(name, "default_nt");
    break;
  case 55:
    strcpy(name, "value");
    break;
  case 56:
    strcpy(name, "caseStmts2");
    break;
  case 57:
    strcpy(name, "range");
    break;
  case 58:
    strcpy(name, "input_stmt");
    break;
  case 59:
    strcpy(name, "output_stmt");
    break;
  case 60:
    strcpy(name, "for_loop");
    break;
  case 61:
    strcpy(name, "while_loop");
    break;
  case 62:
    strcpy(name, "caseStmtNode");
    break;
  }
}