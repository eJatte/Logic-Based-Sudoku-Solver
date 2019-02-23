#include "sudokuSolver_2.h"


void solve_sudoku(int *cells, bool message){
	s = message;
	bool *candidates[81] = {0};
	for(int i = 0; i < 81; i++)
		candidates[i] = calloc(9,sizeof(bool));

	updateCandidates(cells, candidates);

	bool *checkedBoxNumbers[9] = {0};
	for(int i = 0; i < 9; i++)
		checkedBoxNumbers[i] = calloc(9, sizeof(bool));

	bool *checkedPairs[9] = {0};
	for(int i = 0; i < 9; i++)
		checkedPairs[i] = calloc(9, sizeof(bool));

	bool *checkedRows[9] = {0};
	for(int i = 0; i < 9; i++)
		checkedRows[i] = calloc(9, sizeof(bool));

	bool *checkedCollumns[9] = {0};
	for(int i = 0; i < 9; i++)
		checkedCollumns[i] = calloc(9, sizeof(bool));
	//bool checkedRows[9] = {0};

	bool solved = false;
	while(!solved){
		while(check_single(cells, candidates)){}

		if(check_unique_rows(cells, candidates)){
			continue;
		}

		if(check_unique_collumns(cells, candidates)){
			continue;
		}

		if(check_unique_boxes(cells, candidates)){
			continue;
		}

		if(check_unique_boxes_rows(cells, candidates, checkedBoxNumbers)){
			continue;
		}

		if(check_unique_boxes_collumns(cells, candidates, checkedBoxNumbers)){
			continue;
		}

		if(check_unique_boxes_pair_collumns(cells, candidates, checkedPairs)){
			continue;
		}

		if(check_unique_boxes_pair_rows(cells, candidates, checkedPairs)){
			continue;
		}

		if(check_forced_rows(cells, candidates, checkedRows)){
			continue;
		}

		if(check_forced_collumns(cells, candidates, checkedCollumns)){
			continue;
		}

		break;
	}

	for(int i = 0; i <9; i++)
		free(checkedCollumns[i]);
	for(int i = 0; i <9; i++)
		free(checkedRows[i]);
	for(int i = 0; i <9; i++)
		free(checkedPairs[i]);
	for(int i = 0; i < 9; i++)
		free(checkedBoxNumbers[i]);
	for(int i = 0; i < 81; i++)
		free(candidates[i]);
}

int check_forced_collumns(int *cells, bool **candidates, bool **checkedCollumns){
	for(int x = 0; x < 9; x++){
		if(check_forced_collumn(cells, candidates, checkedCollumns, x))
			return 1;
	}
	return 0;
}

int check_forced_collumn(int *cells, bool **candidates, bool **checkedCollumns, int collumn){
	for(int y = 0; y < 9; y++){
		if(cells[p2i(collumn,y)] != 0){
			checkedCollumns[collumn][cells[p2i(collumn,y)]-1] = 1;
		}
	}

	for(int n = 0; n < 9; n++){
		if(checkedCollumns[collumn][n])
			continue;
		int must_yx = -1;
		for(int yx = 0; yx < 3; yx++){
			for(int y = 0; y < 3; y++){
				if(candidates[p2i(collumn,yx*3+y)][n] == false){
					if(must_yx != -1){
						must_yx = -1;
						yx = 3;
						break;
					}
					must_yx = yx;
				}
			}
		}
		if(must_yx != -1){
			update_collumn_box(cells, candidates, n+1, must_yx, collumn);
			checkedCollumns[collumn][n] = true;
			printf("collumn %d n = %d\n", collumn%3, n+1);
			for(int x = (collumn/3)*3; x < (collumn/3)*3+3; x++){
				for(int y = must_yx*3; y < must_yx*3+3; y++){
					if(candidates[p2i(x,y)][n] && cells[p2i(x,y)] == 0)
						printf(" ,");
					else if (cells[p2i(x,y)] == 0)
						printf("%d,",n+1);
					else
						printf("%d,",cells[p2i(x,y)]);
				}
				printf("\n");
			}
			return 1;
		}
	}
	return 0;
}

int check_forced_rows(int *cells, bool **candidates, bool **checkedRows){
	for(int y = 0; y < 9; y++){
		if(check_forced_row(cells, candidates, checkedRows, y))
			return 1;
	}
	return 0;
}

int check_forced_row(int *cells, bool **candidates, bool **checkedRows, int row){
	for(int x = 0; x < 9; x++){
		if(cells[p2i(x,row)] != 0){
			checkedRows[row][cells[p2i(x,row)]-1] = 1;
		}
	}

	for(int n = 0; n < 9; n++){
		if(checkedRows[row][n])
			continue;
		int must_bx = -1;
		for(int bx = 0; bx < 3; bx++){
			for(int x = 0; x < 3; x++){
				if(candidates[p2i(bx*3+x,row)][n] == false){
					if(must_bx != -1){
						must_bx = -1;
						bx = 3;
						break;
					}
					must_bx = bx;
				}
			}
		}
		if(must_bx != -1){
			update_row_box(cells, candidates, n+1, must_bx, row);
			checkedRows[row][n] = true;
			printf("row\n");
			return 1;
		}
	}
	return 0;
}

int check_unique_boxes_pair_rows(int *cells, bool **candidates, bool **checkedPairs){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(check_unique_box_pair_rows(cells, candidates,checkedPairs, x,y)){
				return 1;
			}
		}
	}
	return 0;
}

int check_unique_box_pair_rows(int *cells, bool **candidates, bool **checkedPairs, int x, int y){
	int cellValues[9] = {1,1,1,1,1,1,1,1,1};
	int primes[9] = {2,3,5,7,11,13,17,19,23};
	bool hasTwo[9] = {0};
	for(int yi = 0; yi < 3; yi++ ){
		for(int xi = 0; xi < 3; xi++){
			int numCandidates = 0;
			for(int i = 0; i < 9; i++){
				if(candidates[p2i(xi+x*3,yi+y*3)][i] == false){
					cellValues[yi*3+xi] *= primes[i];
					numCandidates++;
				}
			}
			if(numCandidates == 2 && !checkedPairs[p2i_3x3(x,y)][yi*3+xi] && cells[p2i(x*3+xi,y*3+yi)] == 0)
				hasTwo[yi*3+xi] = true;
		}
	}

	for(int yi = 0; yi < 3; yi++){
		for(int xi = 0; xi < 2; xi++){
			if(hasTwo[yi*3+xi]){
				for(int pi = xi+1; pi < 3; pi++){
					if(hasTwo[yi*3+pi] && cellValues[yi*3+xi] == cellValues[yi*3+pi]){
						checkedPairs[p2i_3x3(x,y)][yi*3+xi] = true;
						checkedPairs[p2i_3x3(x,y)][yi*3+pi] = true;
						int first = 1;
						for(int n = 0; n < 9; n++){
							if(candidates[p2i(xi+x*3,yi+y*3)][n] == false){
								update_pair_row(cells, candidates, n+1,yi+y*3,xi+x*3,pi+x*3);
								update_pair_box(cells, candidates, n+1,yi*3+xi,yi*3+pi,x,y);
								if(s){
									if(first == 1)
										printf("pair collumn: value %d",n+1);
									else if(first == 0){
										printf(" and %d at box (%d,%d) at cell (%d,%d) and (%d,%d)\n",n+1,x,y,xi+x*3,yi+y*3,pi+x*3,yi+y*3);
									}
								}
								if(first == 0)
									return 1;
								first = 0;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int check_unique_boxes_pair_collumns(int *cells, bool **candidates, bool **checkedPairs){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(check_unique_box_pair_collumns(cells, candidates,checkedPairs, x,y)){
				return 1;
			}
		}
	}
	return 0;
}

int check_unique_box_pair_collumns(int *cells, bool **candidates, bool **checkedPairs, int x, int y){
	int cellValues[9] = {1,1,1,1,1,1,1,1,1};
	int primes[9] = {2,3,5,7,11,13,17,19,23};
	bool hasTwo[9] = {0};

	for(int yi = 0; yi < 3; yi++ ){
		for(int xi = 0; xi < 3; xi++){
			int numCandidates = 0;
			for(int i = 0; i < 9; i++){
				if(candidates[p2i(xi+x*3,yi+y*3)][i] == false){
					cellValues[yi*3+xi] *= primes[i];
					numCandidates++;
				}
			}
			if(numCandidates == 2 && !checkedPairs[p2i_3x3(x,y)][yi*3+xi] && cells[p2i(x*3+xi,y*3+yi)] == 0)
				hasTwo[yi*3+xi] = true;
		}
	}

	for(int xi = 0; xi < 3; xi++){
		for(int yi = 0; yi < 2; yi++){
			if(hasTwo[yi*3+xi]){
				for(int pi = yi+1; pi < 3; pi++){
					if(hasTwo[pi*3+xi] && cellValues[yi*3+xi] == cellValues[pi*3+xi]){
						checkedPairs[p2i_3x3(x,y)][yi*3+xi] = true;
						checkedPairs[p2i_3x3(x,y)][pi*3+xi] = true;
						int first = 1;
						for(int n = 0; n < 9; n++){
							if(candidates[p2i(xi+x*3,yi+y*3)][n] == false){
								update_pair_collumn(cells, candidates, n+1,xi+x*3,yi+y*3,pi+y*3);
								update_pair_box(cells, candidates, n+1,yi*3+xi,pi*3+xi,x,y);
								if(s){
									if(first == 1)
										printf("pair collumn: value %d",n+1);
									else if(first == 0){
										printf(" and %d at box (%d,%d) at cell (%d,%d) and (%d,%d)\n",n+1,x,y,xi+x*3,yi+y*3,xi+x*3,pi+y*3);
									}
								}
								if(first == 0)
									return 1;
								first = 0;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int check_unique_boxes_collumns(int *cells, bool **candidates, bool **checkedBoxNumbers){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(check_unique_box_collumns(cells, candidates,checkedBoxNumbers, x,y)){
				return 1;
			}
		}
	}
	return 0;
}

int check_unique_box_collumns(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y){
	for(int n = 0; n < 9; n++){
		if(checkedBoxNumbers[p2i_3x3(x,y)][n])
			continue;
		int yn = -1;
		int xn = -1;
		for(int xi = x*3; xi < x*3+3; xi++){
			for(int yi = y*3; yi < y*3+3; yi++){
				if(candidates[p2i(xi,yi)][n] == false && cells[p2i(xi,yi)] == 0){
					if(xn != -1 && yn != -1){
						xn = -1;
						yn = -1;

						xi = x*3+3;
						break;
					}
					xn = xi;
					yn = yi;
					break;
				}
			}
		}

		if(xn != -1 && yn != -1){
			update_box_collumn(cells, candidates, n+1,y,xn);
			checkedBoxNumbers[p2i_3x3(x,y)][n] = true;
			if(s)
				printf("unique_box_collumn: %d in box (%d,%d) in collumn %d\n", n+1, x, y,xn);
			return 1;
		}
	}
	return 0;
}

int check_unique_boxes_rows(int *cells, bool **candidates, bool **checkedBoxNumbers){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(check_unique_box_rows(cells, candidates,checkedBoxNumbers, x,y)){
				return 1;
			}
		}
	}
	return 0;
}

int check_unique_box_rows(int *cells, bool **candidates, bool **checkedBoxNumbers, int x, int y){
	for(int n = 0; n < 9; n++){
		if(checkedBoxNumbers[p2i_3x3(x,y)][n])
			continue;
		int yn = -1;
		int xn = -1;
		for(int yi = y*3; yi < y*3+3; yi++){
			for(int xi = x*3; xi < x*3+3; xi++){
				if(candidates[p2i(xi,yi)][n] == false && cells[p2i(xi,yi)] == 0){
					if(xn != -1 && yn != -1){
						xn = -1;
						yn = -1;

						yi = y*3+3;
						break;
					}
					xn = xi;
					yn = yi;
					break;
				}
			}
		}

		if(xn != -1 && yn != -1){
			update_box_row(cells, candidates, n+1,x,yn);
			checkedBoxNumbers[p2i_3x3(x,y)][n] = true;
			if(s)
				printf("unique_box_row: %d in box (%d,%d) in row %d\n", n+1, x, y,yn);
			return 1;
		}
	}
	return 0;
}

int check_unique_boxes(int *cells, bool **candidates){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(check_unique_box(cells, candidates, x,y)){
				return 1;
			}
		}
	}
	return 0;
}

int check_unique_box(int *cells, bool **candidates, int x, int y){
	for(int n = 0; n < 9; n++){
		int yn = -1;
		int xn = -1;
		for(int yi = y*3; yi < y*3+3; yi++){
			for(int xi = x*3; xi < x*3+3; xi++){
				if(candidates[p2i(xi,yi)][n] == false && cells[p2i(xi,yi)] == 0){
					if(xn != -1 && yn != -1){
						xn = -1;
						yn = -1;

						yi = y*3+3;
						break;
					}
					xn = xi;
					yn = yi;
				}
			}
		}
		if(xn != -1 && yn != -1){
			cells[p2i(xn,yn)] = n+1;
			updateCandidates_cell(cells, candidates, p2i(xn,yn));
			if(s)
				printf("unique_box: added %d at cell (%d,%d)\n", n+1, xn, yn);
			return 1;
		}
	}
	return 0;
}

int check_unique_collumns(int *cells, bool **candidates){
	for(int x = 0; x < 9; x++){
		if(check_unique_collumn(cells, candidates, x)){
			return 1;
		}
	}
	return 0;
}

int check_unique_collumn(int *cells, bool **candidates, int x){
	for(int n = 0; n < 9; n++){
		int yn = -1;
		for(int y = 0; y < 9; y++){
			if(candidates[p2i(x,y)][n] == false && cells[p2i(x,y)] == 0){
				if(yn != -1){
					yn = -1;
					break;
				}
				yn = y;
			}
		}
		if(yn != -1){
			cells[p2i(x,yn)] = n+1;
			updateCandidates_cell(cells, candidates, p2i(x,yn));
			if(s)
				printf("unique_collumn: added %d at cell (%d,%d)\n", n+1, x,yn);
			return 1;
		}
	}
	return 0;
}

int check_unique_rows(int *cells, bool **candidates){
	for(int y = 0; y < 9; y++){
		if(check_unique_row(cells, candidates, y)){
			return 1;
		}
	}
	return 0;
}

int check_unique_row(int *cells, bool **candidates, int y){
	for(int n = 0; n < 9; n++){
		int xn = -1;
		for(int x = 0; x < 9; x++){
			if(candidates[p2i(x,y)][n] == false && cells[p2i(x,y)] == 0){
				if(xn != -1){
					xn = -1;
					break;
				}
				xn = x;
			}
		}
		if(xn != -1){
			cells[p2i(xn,y)] = n+1;
			updateCandidates_cell(cells, candidates, p2i(xn,y));
			if(s)
				printf("unique_row: added %d at cell (%d,%d)\n", n+1, xn,y);
			return 1;
		}
	}
	return 0;
}

int check_single(int *cells, bool **candidates){
	for(int y = 0; y < 9; y++){
		for(int x = 0; x < 9; x++){
			if(cells[p2i(x,y)] == 0){
				if(check_single_cell(cells, candidates, p2i(x,y))){
					updateCandidates_cell(cells, candidates, p2i(x,y));
					if(s)
						printf("single: added %d at cell (%d,%d)\n",cells[p2i(x,y)],x,y);
					return 1;
				}
			}
		}
	}
	return 0;
}

int check_single_cell(int *cells, bool **candidates, int cellIndex){
	int n = -1;
	for(int i = 0; i < 9; i++){
		if(candidates[cellIndex][i] == false){
			if(n != -1)
				return 0;
			n = i+1;
		}
	}
	if(n != -1)
		cells[cellIndex] = n;
	else
		return 0;
	return 1;
}

void updateCandidates(int *cells, bool **candidates){
	for(int i = 0; i < 81; i++){
		updateCandidates_cell(cells, candidates, i);
	}
}

void updateCandidates_cell(int *cells, bool **candidates, int cellIndex){
	if(cells[cellIndex] == 0)
		return;
	updateRow_cell(cells, candidates, cellIndex);
	updateCollumn_cell(cells, candidates, cellIndex);
	updateBox_cell(cells,candidates, cellIndex);
}

void updateRow_cell(int *cells, bool **candidates, int cellIndex){
	int x = cellIndex%9;
	int y = cellIndex/9;

	for(int xi = 0; xi < 9; xi++){
		if(xi != x && cells[p2i(xi,y)] == 0){
			candidates[p2i(xi,y)][cells[p2i(x,y)]-1] = true;
		}
	}
}

void updateCollumn_cell(int *cells, bool **candidates, int cellIndex){
	int x = cellIndex%9;
	int y = cellIndex/9;

	for(int yi = 0; yi < 9; yi++){
		if(yi != y && cells[p2i(x,yi)] == 0){
			candidates[p2i(x,yi)][cells[p2i(x,y)]-1] = true;
		}
	}
}

void updateBox_cell(int *cells, bool **candidates, int cellIndex){
	int x = cellIndex%9;
	int y = cellIndex/9;

	int x_box = x/3;
	int y_box = y/3;

	for(int yi = y_box*3; yi < y_box*3+3; yi++){
		for(int xi = x_box*3; xi < x_box*3+3; xi++){
			if(!(yi == y && xi == x) && cells[p2i(xi,yi)] == 0){
				candidates[p2i(xi,yi)][cells[p2i(x,y)]-1] = true;
			}
		}
	}
}

void update_box_row(int *cells, bool **candidates, int n, int x, int row){
	for(int xi = 0; xi < 9; xi++){
		if(xi/3 != x && cells[p2i(xi,row)] == 0){
			candidates[p2i(xi,row)][n-1] = true;
		}
	}
}

void update_box_collumn(int *cells, bool **candidates, int n, int y, int collumn){
	for(int yi = 0; yi < 9; yi++){
		if(yi/3 != y && cells[p2i(collumn, yi)] == 0){
			candidates[p2i(collumn,yi)][n-1] = true;
		}
	}
}

void update_pair_collumn(int *cells, bool **candidates, int n, int collumn, int y1, int y2){
	for(int yi = 0; yi < 9; yi++){
		if(yi != y1 && yi != y2 && cells[p2i(collumn, yi)] == 0){
			candidates[p2i(collumn, yi)][n-1] = true;
		}
	}
}

void update_pair_row(int *cells, bool **candidates, int n, int row, int x1, int x2){
	for(int xi = 0; xi < 9; xi++){
		if(xi != x1 && xi != x2 && cells[p2i(xi, row)] == 0){
			candidates[p2i(xi, row)][n-1] = true;
		}
	}
}

void update_pair_box(int *cells, bool **candidates, int n, int i1, int i2, int bx, int by){
	for(int i = 0; i < 9; i++){
		if(i != i1 && i != i2 && cells[p2i(bx*3+i%3,by*3+i/3)] == 0){
			candidates[p2i(bx*3+i%3,by*3+i/3)][n-1] = true;
		}
	}
}

void update_row_box(int *cells, bool **candidates, int n, int bx, int row){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(x == row%3)
				break;
			if(cells[p2i(bx*3+x,row/3+y)] != 0){
				candidates[p2i(bx*3+x, row/3+y)][n-1] = true;
			}
		}

	}
}

void update_collumn_box(int *cells, bool **candidates, int n, int yx, int collumn){
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(y == collumn%3)
				break;
			if(cells[p2i(collumn/3+x, yx*3+y)] != 0){
				candidates[p2i(collumn/3+x, yx*3+y)][n-1] = true;
			}
		}

	}
}

int hasWon(int *cells){
	for(int i = 0; i < 81; i++){
		if(cells[i] == 0)
			return 0;
	}

	for(int i = 0; i < 9; i++){
		if(row_won(cells, i) == 0 || collumn_won(cells, i) == 0){
			return 0;
		}
	}

	return 1;
}

int box_won(int *cells, int x, int y){
	int count[9] = {0};
	for(int xi = x*3; xi < x*3+3; xi++){
		for(int yi = y*3; yi < y*3+3; yi++){
			count[cells[p2i(xi,yi)]-1]++;
			if(count[cells[p2i(xi,yi)]-1] > 1){
				return 0;
			}
		}
	}
	return 1;
}

int row_won(int *cells, int r){
	int count[9] = {0};
	for(int i = 0; i < 9; i++){
		count[cells[p2i(r,i)]-1]++;
		if(count[cells[p2i(r,i)]-1] > 1){
			return 0;
		}
	}
	return 1;
}

int collumn_won(int *cells, int c){
	int count[9] = {0};
	for(int i = 0; i < 9; i++){
		count[cells[p2i(i,c)]-1]++;
		if(count[cells[p2i(i,c)]-1] > 1){
			return 0;
		}
	}
	return 1;
}

void printCells(int *cells){
	for(int y = 0; y < 9; y++){
		for(int x = 0; x < 9; x++){
			printf("%d,", cells[p2i(x,y)]);
			if(x%3 == 2 && x != 0)
				printf(" ");
		}
		printf("\n");
		if(y%3 == 2 && y != 0)
			printf("\n");
	}
}

void printCandidates(int *cells, bool **candidates){
	for(int y = 0; y < 9; y++){
		for(int x = 0; x < 9; x++){
			if(cells[p2i(x,y)] == 0)
				printCandidates_cell(candidates, p2i(x,y));
		}
		printf("\n");
	}
}

void printCandidates_cell(bool **candidates, int cellIndex){
	int x = cellIndex%9;
	int y = cellIndex/9;

	printf("(%d,%d): ", x,y);
	for(int i = 0; i < 9; i++){
		if(candidates[p2i(x,y)][i] == false)
			printf("%d,",i+1);
	}
	printf("\n");
}

int p2i(int x, int y){
	return y*9+x;
}

int p2i_3x3(int x, int y){
	return y*3+x;
}
