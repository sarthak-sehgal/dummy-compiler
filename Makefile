run : driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o
	gcc driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o -o output -lm

debug_exe : driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o
	gcc driver.o general.o terminal_name.o nonterminal_name.o terminal_map.o nonterminal_map.o grammar_reader.o grammar.o hash_map.o print.o -o debug_exe -lm

exe : driver.o general.o
	gcc driver.o general.o -o exe

terminal_name.o : ./utils/terminal_name.h ./utils/terminal_name.c
	gcc -c ./utils/terminal_name.c

nonterminal_name.o : ./utils/nonterminal_name.h ./utils/nonterminal_name.c
	gcc -c ./utils/nonterminal_name.c

terminal_map.o : ./utils/terminal_map.h ./utils/terminal_map.c
	gcc -c ./utils/terminal_map.c

hash_map.o : ./data_structures/hash_map.h ./data_structures/hash_map.c
	gcc -c ./data_structures/hash_map.c

nonterminal_map.o : ./utils/nonterminal_map.h ./utils/nonterminal_map.c
	gcc -c ./utils/nonterminal_map.c

grammar_reader.o : ./utils/grammar_reader.h ./utils/grammar_reader.c
	gcc -c ./utils/grammar_reader.c

grammar.o : ./data_structures/grammar.h ./data_structures/grammar.c
	gcc -c ./data_structures/grammar.c

driver.o : driver.c
	gcc -c driver.c

general.o : ./utils/general.h ./utils/general.c
	gcc -c ./utils/general.c

print.o : ./utils/print.h ./utils/print.c
	gcc -c ./utils/print.c

clean :
	rm *.o