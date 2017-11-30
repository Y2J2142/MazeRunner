#pragma once
#include "Room.h"
#include <iostream>
static long int counter = 0;
class Maze
{
public:
	int R;
	int C;
	int s_x, s_y;
	int e_x, e_y;
	Room** maze;


	Maze(int, int);
	~Maze();
	void make_path(int, int);
	bool find_path(int, int);
	void reset_visited();
	friend std::ostream&  operator << (std::ostream& o, const Maze& maze);
};

