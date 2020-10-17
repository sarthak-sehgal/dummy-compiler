/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdbool.h>

#ifndef ENTITIES_H
#define ENTITIES_H

// TO DO: Change Values
#define NUM_NT 58
#define NUM_T 58
#define MAX_SYMBOL_LEN 25

/*
  List of terminal symbols in the grammar
*/
enum __TERMINAL__
{
  // TO DO: edit of terminals here
  DECLARE,
  MODULE,
  ID,
  SEMICOL,
  DRIVERDEF,
  DRIVER,
  PROGRAM,
  DRIVERENDDEF,
  DEF,
  ENDDEF,
  TAKES,
  INPUT,
  SQBO,
  SQBC,
  RETURNS,
  COLON,
  COMMA,
  INTEGER,
  REAL,
  BOOLEAN,
  ARRAY,
  OF,
  RANGEOP,
  START,
  END,
  BO,
  BC,
  GET_VALUE,
  PRINT,
  TRUE,
  FALSE,
  NUM,
  RNUM,
  ASSIGNOP,
  USE,
  WITH,
  PARAMETERS,
  PLUS,
  MINUS,
  MUL,
  DIV,
  AND,
  OR,
  LT,
  LE,
  GT,
  GE,
  EQ,
  NE,
  SWITCH,
  CASE,
  BREAK,
  DEFAULT,
  FOR,
  IN,
  WHILE,
  EPS,
  DOLLAR
};
typedef enum __TERMINAL__ terminal;

/*
  List of non-terminal symbols in the grammar
*/
enum __NONTERMINAL__
{
  // TO DO: edit list of non terminals here
  program,
  moduleDeclarations,
  otherModules,
  driverModule,
  otherModule,
  moduleDeclaration,
  module,
  moduleDef,
  input_plist,
  ret,
  output_plist,
  dataType,
  input_plist2,
  type,
  output_plist2,
  range_arrays,
  index_nt,
  statements,
  statement,
  ioStmt,
  simpleStmt,
  declareStmt,
  condionalStmt,
  iterativeStmt,
  var,
  boolConstt,
  var_id_num,
  whichId,
  assignmentStmt,
  moduleReuseStmt,
  whichStmt,
  lvalueIDStmt,
  lvalueARRStmt,
  expression,
  optional,
  idList,
  idList2,
  arithmeticOrBooleanExpr,
  unary_nt,
  unary_op,
  new_NT,
  arithmeticExpr,
  AnyTerm,
  arithmeticOrBooleanExpr2,
  logicalOp,
  AnyTerm2,
  relationalOp,
  term,
  arithmeticExpr2,
  op1,
  factor,
  term2,
  op2,
  caseStmts,
  default_nt,
  value,
  caseStmts2,
  range,
  input_stmt,  //extra (for semantics only)
  output_stmt, //extra (for semantics only)
  for_loop,    //extra (for semantics only)
  while_loop,  //extra (for semantics only)
  caseStmtNode
};
typedef enum __NONTERMINAL__ nonterminal;

/*
  Identifies the token with a terminal or nonterminal
*/
union __GRAMMAR_TOKEN__
{
  terminal t;
  nonterminal nt;
};
typedef union __GRAMMAR_TOKEN__ gm_token;

/*
  Production rule is treated as a list of nodes where each node is a terminal or non-terminal
*/
typedef struct __GRAMMAR_NODE__ gm_node;
struct __GRAMMAR_NODE__
{
  bool is_terminal;
  gm_token gmt;
  gm_node *next;
};

/* Production rule has a non-terminal LHS and head of the RHS Linked List */
struct __GRAMMAR_PROD_RULE__
{
  nonterminal lhs;
  gm_node *rhs;
};
typedef struct __GRAMMAR_PROD_RULE__ gm_prod_rule;

#endif