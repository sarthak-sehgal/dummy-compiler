/*
  GROUP NO. 21
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./entities.h"
#include "./hash_map.h"
#include "./terminal_map.h"
#include "./nonterminal_map.h"
#include "./grammar.h"
#include "./tokeniser.h"
#include "./parser.h"
#include "./grammar_reader.h"
#include "./print.h"
#include "./type_exp_table.h"
#include "./errors.h"
#include "./driver.h"

char grammar_file[150] = "./grammar.txt";
char *source_code_file;
bool grammar_read = false, tokenised = false, pt_created = false, type_table_created = false, error_container_created = false;
grammar *G = NULL;
token_stream *ts = NULL;
parse_tree_node *pt_root = NULL;
hash_map *type_table = NULL;
error_container *err_container = NULL;

void initialise()
{
  if (!grammar_read)
  {
    G = init_grammar();
    read_grammar(grammar_file, G);
    grammar_read = true;
  }
  if (!tokenised)
  {
    ts = init_token_stream();
    tokenise_source_code(source_code_file, ts);
    tokenised = true;
  }
  if (!pt_created)
  {
    create_parse_tree(&pt_root, G, ts);
    pt_created = true;
  }
}

void init_type_table()
{
  if (!error_container_created)
  {
    err_container = init_error_container();
    error_container_created = true;
  }
  if (!type_table_created)
  {
    type_table = init_type_exp_table();
    traverse_parse_tree(pt_root, type_table, err_container);
    type_table_created = true;
  }
}

int main(int argc, char **argv)
{
  assert(argc >= 2, "missing arg for source code file");
  source_code_file = argv[1];
  while (true)
  {
    printf("\n");
    printf("Options: \n");
    printf("0. Exit\n");
    printf("1. Create Parse Tree\n");
    printf("2. Print Type Errors\n");
    printf("3. Print Parse Tree\n");
    printf("4. Print Type Expression Table\n");

    int input;
    printf("\nSelect option> ");
    scanf("%d", &input);
    printf("\n");

    switch (input)
    {
    case 0:
      printf("Exiting...\n");
      return 0;
      break;

    case 1: // create parse tree
      initialise();
      printf("\nParse tree created!\n");
      break;
    case 2: // print type errors
      initialise();
      init_type_table();
      print_errors(err_container);
      break;
    case 3: // print parse tree
      initialise();
      init_type_table();
      print_parse_tree(pt_root);
      break;
    case 4: // print type expression table
      initialise();
      init_type_table();
      print_type_exp_table(type_table);
      print_invalid_vars(err_container->invalid_vars);
      break;
    default:
      printf("Please select a valid option.\n\n");
      break;
    }
  }

  return 0;
}