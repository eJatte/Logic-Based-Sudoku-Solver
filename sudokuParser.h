#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SUDOPARSER_H
#define SUDOPARSER_H

void parseCheatSudoku(int *cells, char *cheat, char *mask);
int parseSudoku(int *cells, char *sudoku);
#endif
