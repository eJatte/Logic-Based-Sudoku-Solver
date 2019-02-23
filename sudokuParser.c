#include "sudokuParser.h"


void parseCheatSudoku(int *cells, char *cheat, char *mask){
	for(int i = 0; i < 81; i++){
		if(mask[i] == '0'){
			cells[i] = cheat[i]-'0';
		}
	}
}

int parseSudoku(int *cells, char *sudoku){
	for(int i = 0; i < 81; i++){
		cells[i] = sudoku[i]-'0';
		if(cells[i] < 0 || cells[i] > 9){
			return -1;
		}
	}
	return 0;
}
