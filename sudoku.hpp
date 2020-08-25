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

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>


class Sudoku{
	public:
	    // Solve a sudoku from file.
		static std::vector<std::vector<int>> solve(std::string);
		static int** solve9x9(std::string);

		// Check if a 2D matrix is a valid sudoku.
		static bool isValid(std::vector<std::vector<int>>&);
		static bool isValid9x9(int[9][9]);

		// Algorithms for solving sudokus.
		static bool backtracking(std::vector<std::vector<int>>&);
		static bool backtracking9x9(int[9][9]);

		// Print out a sudoku.
		static void print(std::vector<std::vector<int>>&);
		static void print9x9(int[9][9]);
	private:
	    // Legality of a sudoku after inserting a number.
		static bool isLegal(std::vector<std::vector<int>>&, int, int, int);
		static bool isLegal9x9(int[9][9], int, int, int);
};


/**
 * Solve a nxn sudoku, taking the puzzle from the file
 * and return a vector of vector of int.
 * The file containing the sudoku must be in the form:
 *      n
 *      a b c ... d
 *      . .       .
 *      .    .    .
 *      .       . .
 *      e f g ... h
 * There are n rows and n columns.
 * The empty cells in the sudoku must be represented with zeros.
 * The file must contain only numbers in range [0, n].
 *
 * The matrix returned is copied in the std::vector given:
 * 		std::vector<std::vector<int>> foo = Sudoku::solve(fileName);
 *
 * @param str Name of the file containing the sudoku to solve.
 * @return 2D matrix containing the solved sudoku.
 */
std::vector<std::vector<int>> Sudoku::solve(std::string str){
	int s, k;
	std::ifstream f(str);
	if(f.is_open()){
        f >> s;
    }
    else{
        std::cout << "Error: file not found" << std::endl;
        exit(1);
    }
    std::vector<int> tmp(s, 0);
    std::vector<std::vector<int>> sudoku(s, tmp);
    for(int i = 0; i < s; ++i){
        for(int j = 0; j < s; ++j){
            f >> k;
            if(k <= s && k >= 0){
                sudoku[i][j] = k;
            }
            else{
                std::cout << "Error: number not in range" << std::endl;
                exit(1);
            }
        }
    }
    if(!Sudoku::isValid(sudoku)){
        std::cout << "Error: given sudoku is not legal" << std::endl;
        exit(1);
    }
	if(!Sudoku::backtracking(sudoku)){
        std::cout << "Error: given sudoku is not solvable" << std::endl;
        exit(1);
	}
	return sudoku;
}

/**
 * Solve a 9x9 sudoku, taking the puzzle from the file
 * and return a int** (int[9][9]).
 * The file containing the sudoku must be in the form:
 *      9
 *      a b c d e f g h i
 *      f g h j z r s r n
 *      q c g h m y u i l
 *      q z a y u i l k h
 *      a b c d e f g h i
 *      f g h j z r s r n
 *      q c g h m y u i l
 *      q z a y u i l k h
 *      t y n f d e r y j
 * There are 9 rows and 9 columns.
 * The empty cells in the sudoku must be represented with zeros.
 * The file must contain only numbers in range [0, 9].
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
 * @return 2D matrix containg the solved sudoku.
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
 * Check if a 2D matrix is a valid sudoku.
 */
bool Sudoku::isValid(std::vector<std::vector<int>>& sudoku){
    // TODO
    return true;
}

/**
 * Check if a 9x9 matrix is a valid sudoku.
 */
bool Sudoku::isValid9x9(int sudoku[9][9]){
    // TODO
    return true;
}


/**
 * Solve a nxn sudoku using backtracking.
 * It modifies the parameter passed.
 *
 * @param sudoku 2D matrix containing the sudoku to solve.
 * @return True if is solved, false if it fails to solve.
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
 * @return True if is solved, false if it fails to solve.
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
 * Print a nxn sudoku.
 *
 * @param sudoku The nxn sudoku to print.
 */
void Sudoku::print(std::vector<std::vector<int>>& sudoku){
    int s = sudoku.size();
    int n = std::sqrt(s);
    for(int i = 0; i < s; ++i){
        for(int j = 0; j < s; ++j){
            std::cout << std::setw((int) std::log10(s) + 1) << sudoku[i][j] << " ";
            if(j % n == n-1){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if(i % n == n-1){
                std::cout << std::endl;
        }
    }
    return;
}

/**
 * Print a 9x9 sudoku.
 *
 * @param sudoku The 9x9 sudoku to print.
 */
void Sudoku::print9x9(int sudoku[9][9]){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            std::cout << sudoku[i][j] << " ";
            if(j % 3 == 2){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if(i % 3 == 2){
                std::cout << std::endl;
        }
    }
    return;
}


/**
 * Checks if a legal nxn sudoku remains legal after inserting
 * the value n at row r and column c.
 *
 * @param sudoku The sudoku to check.
 * @param r Row's number.
 * @param c Column's number.
 * @param n Number to insert.
 * @return True if is legal, false if is illegal.
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
 * @param sudoku The sudoku to check.
 * @param r Row's number.
 * @param c Column's number.
 * @param n Number to insert.
 * @return True if is legal, false if is illegal.
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
