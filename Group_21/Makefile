run : driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o token_stream.o tokeniser.o token_map.o pda_stack.o parse_tree.o parser.o type_exp_table.o errors.o
	gcc driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o token_stream.o tokeniser.o token_map.o pda_stack.o parse_tree.o parser.o type_exp_table.o errors.o -o output -lm

exe : driver.o general.o
	gcc driver.o general.o -o exe

terminal_name.o : terminal_name.h terminal_name.c
	gcc -c terminal_name.c

nonterminal_name.o : nonterminal_name.h nonterminal_name.c
	gcc -c nonterminal_name.c

terminal_map.o : terminal_map.h terminal_map.c
	gcc -c terminal_map.c

token_map.o : token_map.h token_map.c
	gcc -c token_map.c

hash_map.o : hash_map.h hash_map.c
	gcc -c hash_map.c

nonterminal_map.o : nonterminal_map.h nonterminal_map.c
	gcc -c nonterminal_map.c

grammar_reader.o : grammar_reader.h grammar_reader.c
	gcc -c grammar_reader.c

grammar.o : grammar.h grammar.c
	gcc -c grammar.c

driver.o : driver.c
	gcc -c driver.c

general.o : general.h general.c
	gcc -c general.c

print.o : print.h print.c
	gcc -c print.c

token_stream.o : token_stream.h token_stream.c
	gcc -c token_stream.c

tokeniser.o : tokeniser.h tokeniser.c
	gcc -c tokeniser.c

parser.o : parser.h parser.c
	gcc -c parser.c

parse_tree.o : parse_tree.h parse_tree.c
	gcc -c parse_tree.c

pda_stack.o : pda_stack.h pda_stack.c
	gcc -c pda_stack.c

type_exp_table.o : type_exp_table.h type_exp_table.c
	gcc -c type_exp_table.c

errors.o : errors.h errors.c
	gcc -c errors.c

clean :
	rm *.o