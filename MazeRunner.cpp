#include <iostream>
#include <stdlib.h>
#include "Maze.h"
#include <random>
//#define R 63
//#define C 235
#define R 31
#define C 51
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> start_r(0, (R-2) / 2); // guaranteed unbiased
std::uniform_int_distribution<int> start_c(0, (C-2) / 2); // guaranteed unbiased



int main()
{
	Maze maze(R, C);
	maze.make_path(start_r(rng) * 2 + 1, start_c(rng) * 2 + 1);
	system("cls");
	system("pause");
	maze.reset_visited();
	maze.find_path(maze.s_x, maze.s_y);
	system("cls");
	std::cout << maze << std::endl;
	system("pause");
    return 0;
}

