#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include "stack.hpp"

void possible_colors(int **, int *, int, int);
bool check_color(int, int, int **, int);
bool solve(int **, int, int, int, int, int, int, Stack, bool, int, int);

#endif
