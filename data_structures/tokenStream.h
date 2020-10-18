/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdlib.h>

//TODO: check what needed 
#include "../utils/general.h"

#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

/*
	TokenStream is a struct having:

*/
typedef struct __TOKEN_STREAM_NODE__ tokenNode;
struct __TOKEN_STREAM_NODE__
{
	int lineNumber;
	char* lexeme;
	char* tokenName;
	tokenNode* next;
	tokenNode* prev;
};


/*
	TokenStream is a struct having:

*/
typedef struct __TOKEN_STREAM__ tokenStream;
struct __TOKEN_STREAM__
{
	int lineCount;
	tokenNode* head;
	tokenNode* tail;
};


tokenStream *init_tokenStream();

tokenNode *init_tokenNode(int lineNumber, char* lexeme, char* tokenName);

void add_new_token(tokenStream* s, tokenNode* node);

#endif