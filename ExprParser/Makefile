DBG = -g
OPT = $(DBG) -Wall -ansi -pedantic -std=c++20

CC = g++ -c $(OPT)
LN = g++

OBJS = main.o Token.o Grammar.o

exprEval: $(OBJS)
	$(LN) -o exprEval $(OBJS)

main.o: main.cpp Token.hpp
	$(CC) main.cpp

Token.o: Token.cpp Token.hpp
	$(CC) Token.cpp

Grammar.o: Grammar.cpp Grammar.hpp Token.hpp
	$(CC) Grammar.cpp

clean:
	/bin/rm -rf $(OBJS) exprEval *~
