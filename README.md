# Maven Securities Interview
Please refer to [MAVEN.md](./MAVEN.md) that provides details about the project along with screenshots.
# Dummy Compiler
This is a _not-so-efficient_ implementation for a compiler for a basic language developed as part of a university course. To view the rules of the language and the complete problem statement, please refer to the [problem statement](https://github.com/sarthak-sehgal/ppl-assignment/blob/master/problem_statement.pdf). The code implements:
1. Grammar and grammar parser
2. Tokeniser
3. Lexer
4. Type expression table generator
5. Type errors generator

## Running locally
```
git clone https://github.com/sarthak-sehgal/dummy-compiler

cd dummy-compiler

make run && ./output t1.txt
```
Note: t1.txt is a sample source code file. The argument can be replaced by any other file (eg: `make run && ./output your_source_code.txt`)

## Developed by
- [Sarthak Sehgal](https://github.com/sarthak-sehgal/)
- [Syed Ahsan Abbas](https://github.com/ahsanabbas123/)
