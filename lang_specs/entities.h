/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdbool.h>

#ifndef ENTITIES_H
#define ENTITIES_H

#define NUM_NT 27
#define NUM_T 33
#define MAX_SYMBOL_LEN 25
#define MAX_RULE_LEN 15

/*
  List of terminal symbols in the grammar
*/
enum __TERMINAL__
{
  DECLARE,
  ID,
  COLON,
  SEMICOL,
  LIST,
  OF,
  VARIABLES,
  JAGGED,
  ARRAY,
  INTEGER,
  R1,
  SQOP,
  NUM,
  SQCL,
  SIZE,
  VALUES,
  CURLOP,
  CURLCL,
  EPS,
  REAL,
  BOOLEAN,
  ELIP,
  EQUALS,
  PLUS,
  MINUS,
  MUL,
  DIV,
  OR,
  AND,
  PROGRAM,
  BROP,
  BRCL,
  COMMA
};
typedef enum __TERMINAL__ terminal;

/*
  List of non-terminal symbols in the grammar
*/
enum __NONTERMINAL__
{
  module,
  decStmtGrp,
  assignStmtGrp,
  decStmt,
  assignStmt,
  primitiveDecStmt,
  jagArrDecStmt,
  primitiveDataType,
  multipleIdList,
  jagArrRange,
  jagArrInit,
  jagArrDimDec,
  jagArrValues,
  numList,
  idList,
  arrayRangeList,
  arrayRange,
  numOrId,
  numOrIdList,
  jagArrElement,
  arrayElement,
  operand,
  assignLhs,
  arithExpression,
  boolExpression,
  term,
  andExpression
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

/*
	Token Stream Node is a struct having:
    - line number
    - lexeme (string)
    - terminal name
    - next and prev pointer to support doubly linked list
*/
typedef struct __TOKEN_STREAM_NODE__ token_node;
struct __TOKEN_STREAM_NODE__
{
  int line_num;
  char *lexeme;
  terminal token_name;
  token_node *next;
  token_node *prev;
};

/**/
typedef struct __PARSE_TREE_NODE__ parse_tree_node;
struct __PARSE_TREE_NODE__
{
  int num_children;
  bool is_terminal;
  int g_rule_idx;
  union
  {
    terminal t;
    nonterminal nt;
  };
  parse_tree_node *children[MAX_RULE_LEN];
};

#endif