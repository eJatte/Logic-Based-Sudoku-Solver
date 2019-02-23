#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SUDOSOLVER_H
#define SUDOSOLVER_H

int s;

int p2i(int x, int y);
int p2i_3x3(int x, int y);

void updateCandidates(int *cells, bool **candidates);

void updateCandidates_cell(int *cells, bool **candidates, int cellindex);

void updateRow_cell(int *cells, bool **candidates, int cellindex);

void updateCollumn_cell(int *cells, bool **candidates, int cellindex);

void updateBox_cell(int *cells, bool **candidates, int cellindex);

void update_box_row(int *cells, bool **candidates, int n, int x, int row);

void update_box_collumn(int *cells, bool **candidates, int n, int y, int collumn);

void update_pair_collumn(int *cells, bool **candidates, int n, int collumn, int y1, int y2);

void update_pair_row(int *cells, bool **candidates, int n, int row, int x1, int x2);

void update_pair_box(int *cells, bool **candidates, int n, int i1, int i2, int bx, int by);

void update_row_box(int *cells, bool **candidates, int n, int bx, int row);

void update_collumn_box(int *cells, bool **candidates, int n, int bx, int row);

void printCells(int *cells);

void printCandidates(int *cells, bool **candidates);

void printCandidates_cell(bool **candidates, int cellindex);

int hasWon(int *cells);

int box_won(int *cells, int x, int y);

int collumn_won(int *cells, int c);

int row_won(int *cells, int r);

void solve_sudoku(int *cells, bool message);

/* Description: Check if any cell has one and only one candidate.
 *				Set correct value if it has.
 *
 * Return:		0 if no singles, >0 if atleast one single
 * */
int check_single(int *cells, bool **candidates);

/* Description: Check if a single cell has one and only one candidate.
 * 				Set correct value if it has.
 *
 * Return:		0 if no single, 1 if single
 * */
int check_single_cell(int *cells, bool **candidates, int cellindex);
/* Description: Check if any row has a unique value which only one cell can
 * 				have. Set that value on that cell if it has.
 *
 * Return:	 	0 if not, 1 otherwise
 * */
int check_unique_rows(int *cells, bool **candidates);
/*
 * Same as rows but for a single row
 * */
int check_unique_row(int *cells, bool **candidates, int y);
/*
 * Same as rows but for collumns
 * */
int check_unique_collumns(int *cells, bool **candidates);
/*
 * Same as collumns but for a single collumn
 * */
int check_unique_collumn(int *cells, bool **candidates, int x);
/*
 * Same as rows but for boxes
 * */
int check_unique_boxes(int *cells, bool **candidates);
/*
 * Same as boxes but for a single box
 * */
int check_unique_box(int *cells, bool **candidates, int x, int y);

/*
 * Check if any box has a value candidate unique for one row
 * */
int check_unique_boxes_rows(int *cells, bool **candidates, bool **checkedBoxNumbers);
/*
 * Same as unique_boxes_rows but for one box
 * */
int check_unique_box_rows(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y);
/*
 * Same as unique_boxes_row but for collumn instead of rows
 * */
int check_unique_boxes_collumns(int *cells, bool **candidates, bool **checkedBoxNumbers);
/*
 * Same as unique_boxes_collumns but for one box
 * */
int check_unique_box_collumns(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y);

int check_unique_boxes_pair_collumns(int *cells, bool **candidates, bool **checkedBoxNumberst);

int check_unique_box_pair_collumns(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y);

int check_unique_boxes_pair_rows(int *cells, bool **candidates, bool **checkedBoxNumberst);

int check_unique_box_pair_rows(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y);

int check_forced_rows(int *cells, bool **candidates, bool **checkedCollumns);

int check_forced_row(int *cells, bool **candidates, bool **checkedCollumns, int collumn);

int check_forced_collumns(int *cells, bool **candidates, bool **checkedCollumns);

int check_forced_collumn(int *cells, bool **candidates, bool **checkedCollumns, int collumn);
#endif
