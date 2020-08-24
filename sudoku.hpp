/**
 * MIT License
 *
 * Copyright (c) 2020 Davide Fassio
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SUDOKU_HPP
#define SUDOKU_HPP

// Used only for debug purpuses.
#include <iostream> 
#include <iomanip>

// Useful libraries.
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>


class Sudoku{
	public:
		static std::vector<std::vector<int>> solve(std::string);
		static int** solve9x9(std::string);
		
		static bool backtracking(std::vector<std::vector<int>>&);
		static bool backtracking9x9(int[9][9]);
	private:
		static bool isLegal(std::vector<std::vector<int>>&, int, int, int);
		static bool isLegal9x9(int[9][9], int, int, int);
};


/**
 * Solve a nxn sudoku, taking the puzzle from the file
 * and return a vector of vector of int.
 *
 * The matrix returned is copied in the std::vector given:
 * 		std::vector<std::vector<int>> foo = Sudoku::solve(fileName);
 *
 * @param str Name of the file containing the sudoku to solve.
 * @returns 2D matrix containing the solved sudoku.
 */
std::vector<std::vector<int>> Sudoku::solve(std::string str){
	// TODO
	std::vector<std::vector<int>> sudoku;
	return sudoku;
}

/**
 * Solve a 9x9 sudoku, taking the puzzle from the file
 * and return a int** (int[9][9]).
 *
 * The int** returned points to a dynamically allocated
 * piece of memory, to free it use:
 * 		int** foo = Sudoku::solve9x9(fileName);
 * 		...
 * 		...
 * 		delete [] foo[0];
 * 		delete [] foo;
 *
 * @param str Name of the file containg the sudoku to solve.
 * @returns 2D matrix containg the solved sudoku.
 */
int** Sudoku::solve9x9(std::string str){
	// TODO
	int** sudoku = new int*[9];
	sudoku[0] = new int[81];
	for(int i = 1; i < 9; ++i){
		sudoku[i] = sudoku[0] + i * 9;
	}

	return sudoku;
}


/**
 * Solve a nxn sudoku using backtracking.
 * It modifies the parameter passed.
 *
 * @param sudoku 2D matrix containing the sudoku to solve.
 * @returns True if is solved, false if it fails to solve.
 */
bool Sudoku::backtracking(std::vector<std::vector<int>> &sudoku){	
	int s = sudoku.size();
	for(int i = 0; i < s; ++i){
		for(int j = 0; j < s; ++j){
			if(sudoku[i][j] == 0){
				for(int k = 1; k < s+1; ++k){
					if(Sudoku::isLegal(sudoku, i, j, k)){
						sudoku[i][j] = k;
						if(Sudoku::backtracking(sudoku)){
							return true;
						}
					}
				}
				sudoku[i][j] = 0;
				return false;
			}	
		} 
	}
	return true;
}

/**
 * Solve a 9x9 sudoku using backtracking.
 * It modifies the parameter passed.
 *
 * @param sudoku 2D matrix containing the sudoku to solve.
 * @returns True if is solved, false if it fails to solve.
 */
bool Sudoku::backtracking9x9(int sudoku[9][9]){
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			if(sudoku[i][j] == 0){
				for(int k = 1; k < 10; ++k){
					if(Sudoku::isLegal9x9(sudoku, i, j, k)){
						sudoku[i][j] = k;
						if(Sudoku::backtracking9x9(sudoku)){
							return true;
						}
					}
				}
				sudoku[i][j] = 0;
				return false;
			}	
		} 
	}
	return true;
}


/**
 * Checks if a legal nxn sudoku remains legal after inserting
 * the value n at row r and column c.
 *
 * @param sudoku the sudoku to check.
 * @param r row's number.
 * @param c column's number.
 * @param n number to insert.
 * @returns True if is legal, false if is illegal.
 */
bool Sudoku::isLegal(std::vector<std::vector<int>> &sudoku, int r, int c, int n){
	int s = sudoku.size();
	int k = std::sqrt(s);
	for(int j = 0; j < s; ++j){
		if(sudoku[r][j] == n){
			return false;
		}
	}
	for(int i = 0; i < s; ++i){
		if(sudoku[i][c] == n){
			return false;
		}
	}
	int br = k * (r / k);
	int bc = k * (c / k);
	for(int i = br; i < br + k; ++i){
		for(int j = bc; j < bc + k; ++j){
			if(sudoku[i][j] == n){
				return false;
			}
		}
	}
	return true;
}

/**
 * Checks if a legal 9x9 sudoku remains legal after inserting
 * the value n at row r and column c.
 *
 * @param sudoku the sudoku to check.
 * @param r row's number.
 * @param c column's number.
 * @param n number to insert.
 * @returns True if is legal, false if is illegal.
 */
bool Sudoku::isLegal9x9(int sudoku[9][9], int r, int c, int n){
	for(int j = 0; j < 9; ++j){
		if(sudoku[r][j] == n){
			return false;
		}
	}
	for(int i = 0; i < 9; ++i){
		if(sudoku[i][c] == n){
			return false;
		}
	}
	int br = 3 * (r / 3);
	int bc = 3 * (c / 3);
	for(int i = br; i < br + 3; ++i){
		for(int j = bc; j < bc + 3; ++j){
			if(sudoku[i][j] == n){
				return false;
			}
		}
	}
	return true;
}
#endif /* SUDOKU_HPP */
