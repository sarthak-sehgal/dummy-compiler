/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lang_specs/entities.h"
#include "./data_structures/hash_map.h"
#include "./utils/terminal_map.h"
#include "./utils/nonterminal_map.h"
#include "./data_structures/grammar.h"
#include "./tokeniser/tokeniser.h"
#include "./parser/parser.h"
#include "./utils/grammar_reader.h"
#include "./utils/print.h"
#include "./driver.h"

int main()
{
  grammar *G = init_grammar();
  token_stream *ts = init_token_stream();
  parse_tree_node *pt_root = NULL;

  char grammar_file[150] = "./grammar.txt";
  char source_code_file[150] = "./source_code.txt";

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

    case 1:
      read_grammar(grammar_file, G);
      // print_grammar(G);
      tokenise_source_code(source_code_file, ts);
      fancy_print_token_stream(ts);
      create_parse_tree(&pt_root, G, ts);
      print_parse_tree_symbols(pt_root);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      printf("Please select a valid option.\n\n");
      break;
    }
  }
}