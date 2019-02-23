#include "sudokuSolver_2.h"
#include "sudokuParser.h"

int readAndSolve(void);

int main(void){
	if(readAndSolve() == -1){
		printf("Not a valid puzzle\n");
		return -1;
	}
	return 0;
}

int readAndSolve(void){
	char *sudoku = calloc(81, sizeof(char));
	int *cells = calloc(81, sizeof(int));

	scanf("%81s",sudoku);

	int ret = parseSudoku(cells, sudoku);

	if(ret == -1){
		return ret;
	}

	printf("Original: \n\n");
	printCells(cells);

	solve_sudoku(cells,true);
	if(hasWon(cells))
		printf("\nStatus: SOLVED\n\n");
	else
		printf("\nStatus: UNSOLVED\n\n");
	printCells(cells);

	return 0;
}
