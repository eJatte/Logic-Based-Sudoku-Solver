CC=gcc
CFLAGS=	-std=gnu11 -Wall -Wextra -Werror -I ../includes/\
	   	-Wmissing-declarations \
		-Wmissing-prototypes \
		-Werror-implicit-function-declaration \
		-Wreturn-type -Wparentheses -Wunused \
		-Wold-style-definition -Wundef -Wshadow \
		-Wstrict-prototypes -Wswitch-default \
		-Wunreachable-code
    
all: SudokuSolver

SudokuSolver: main.o sudokuSolver_2.o sudokuParser.o
	$(CC) -o  SudokuSolver main.o sudokuSolver_2.o sudokuParser.o -lm

main.o: main.c sudokuSolver_2.h sudokuParser.h
	$(CC) -c $*.c $(CFLAGS)

sudokuSolver_2.o: sudokuSolver_2.c
	$(CC) -c $*.c $(CFLAGS)

sudokuParser: sudokuParser.c
	$(CC) -c $*.c $(CFLAGS)

clean:
	rm -f sudokuSolver *.o core

