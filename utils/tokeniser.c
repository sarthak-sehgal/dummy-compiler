/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "tokeniser.h"
#include "token_map.h"
#include "terminal_name.h"

/*
Lexeme possibilites:
  1. Reserved keyword -> list, declare, R1, etc.
  2. Special symbol -> SQOP, SQCL, etc
  3. Number (NUM) -> integer to be checked
  4. Identifiers 
  5. Operators -> only =, +, -, *, /, &&&, |||
*/
char *get_lexeme(char *tokenName, hash_map *tokenMap) {
  int *tokenMapValue = (int *)find_in_map(tokenMap, tokenName);
  char *lexeme = calloc(100, sizeof(char)); //restricts max length of var name declared
  if (tokenMapValue!=NULL) {
    lexeme = tokenName;
    //adding more here tommorow
  }
}


/*
  Tokenise source code from the file
*/
void tokeniseSourceCode(char *file_name, tokenStream *s) {
  
  //generate hashmap which has all reserved keywords  
  hash_map* tokenMap = generate_token_map(25);
  
  char *word = calloc(100, sizeof(char));
  char c; 
  int idx = 0; 

  FILE *fptr = fopen(file_name, "r");
  assert(fptr!=NULL, "source code file opened successfully!");
	
	while(true) 
	{ 
    c = fgetc(fptr);
		if(c == ' ' || c == '\n' || c == EOF) 
		{ 
      // skipping empty lines
      if (idx == 0) {
        s->lineCount++;
        continue;
      }
      word[idx] = '\0';
      lexeme =  get_lexeme(word);
      tokenNode *node = init_tokenNode(s->lineCount, lexeme, word);
      add_new_token(s, node);
      if (c == '\n') s->lineCount++;
      idx = 0; 
		} else { 
      word[idx++] = c;
		} 
    if (c == EOF) break; 
	} 
	fclose(fptr); 
}
