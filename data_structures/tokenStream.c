/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "tokenStream.h"

/*
	Creates a new tokenStream entity.
*/
tokenStream *init_tokenStream() {
	tokenStream* s = (tokenStream *)calloc(1, sizeof(tokenStream));
	s->lineCount = 0;
	s->head = NULL;
	s->tail = NULL;
	return s;
}

/*
	Creates a new tokenNode entity.
*/
tokenNode *init_tokenNode(int lineNumber, char* lexeme, char* tokenName) {
	tokenNode* node = (tokenNode *)calloc(1, sizeof(tokenNode));
	node->lineNumber = lineNumber;
	node->lexeme = lexeme;
	node->tokenName = tokenName;
	node->next = NULL;
	node->prev = NULL;
	return node;
} 

/*
	Adds a tokenNode to the tail of tokenStream.
*/
void add_new_token(tokenStream* s, tokenNode* node) {
	if (s->tail) {
		s->tail->next = node;
		node->prev = s->tail;
		s->tail = node;
	}
	else {
		s->head = node;
		s->tail = node;
	}
}
