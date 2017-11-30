#include "stdafx.h"
#include "Maze.h"
#include "Room.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <Windows.h>
#include <algorithm>

Maze::Maze(int row, int col)
{
	R = row;
	C = col;
	s_x = 1;
	s_y = 0;
	e_x = R - 2;
	e_y = C - 1;
	maze = new Room*[R];
	for (int i = 0; i < R; i++)
		maze[i] = new Room[C];
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			maze[i][j].set_r(i);
			maze[i][j].set_c(j);
			if (i % 2 == 0 || j % 2 == 0)
				maze[i][j].set_wall();
		}
	maze[e_x][e_y].set_path();
}


Maze::~Maze()
{
	for (int i = 0; i < R; i++)
		delete[] maze[i];
	delete[] maze;
}


std::ostream & operator<<(std::ostream & o, const Maze & m)
{
	//o << "start: (" << m.s_x << "," << m.s_y << ") " << "end : (" << m.e_x << "," << m.e_y << ")" << std::endl;
	for (int i = 0; i < m.R; i++)
	{
		for (int j = 0; j < m.C; j++)
		{
			if ((i == m.s_x && j == m.s_y) || (i == m.e_x && j == m.e_y))
			{
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				o << (char)219;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			}
			else
				o << m.maze[i][j];
		}
		o << std::endl;
	}

		
	return o;
			
}

void Maze::reset_visited()
{
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			this->maze[i][j].set_unvisited();
}



void Maze::make_path(int r, int c)
{
	system("cls");
	std::cout << *(this);
	if (!maze[r][c].is_visited())
	{
		maze[r][c].set_visited();
		std::vector<Room*> room_vec;
		if (r - 2 >= 0 && r < R)
			room_vec.push_back(&maze[r - 2][c]);
		if(r+2 < R && r >= 0)
			room_vec.push_back(&maze[r + 2][c]);
		if(c - 2 >= 0 && c < C)
			room_vec.push_back(&maze[r][c - 2]);
		if (c + 2 < C && c >= 0)
			room_vec.push_back(&maze[r][c + 2]);
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(room_vec.begin(), room_vec.end(), std::default_random_engine(seed));
		for (Room* room : room_vec)
		{
			if (!room->is_visited())
			{
				if (r + 2 == room->get_r())
				{
					maze[r + 1][c].set_path();
					make_path(room->get_r(), room->get_c());
				}
				if (r - 2 == room->get_r())
				{
					maze[r - 1][c].set_path();
					make_path(room->get_r(), room->get_c());
				}
				if (c + 2 == room->get_c())
				{
					maze[r][c + 1].set_path();
					make_path(room->get_r(), room->get_c());
				}
				if (c - 2 == room->get_c())
				{
					maze[r][c - 1].set_path();
					make_path(room->get_r(), room->get_c());
				}

			}

		}


	}
}

bool Maze::find_path(int r, int c)
{
	if (r != e_x || c != e_y)
	{
		if (!maze[r][c].is_visited())
		{
			system("cls");
			std::cout << *(this);
			maze[r][c].set_current_path(true);
			maze[r][c].set_visited();
			std::vector<Room*> room_vec;
			if (r - 1 >= 0 && r < R)
				room_vec.push_back(&maze[r - 1][c]);
			if (r + 1 < R && r >= 0)
				room_vec.push_back(&maze[r + 1][c]);
			if (c - 1 >= 0 && c < C)
				room_vec.push_back(&maze[r][c - 1]);
			if (c + 1 < C && c >= 0)
				room_vec.push_back(&maze[r][c + 1]);

			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(room_vec.begin(), room_vec.end(), std::default_random_engine(seed));

			for (Room* room : room_vec)
			{
				if (!room->is_visited() && !room->is_wall())
				{
					if (r + 1 == room->get_r())
						if (find_path(room->get_r(), c))
							return true;
					if (r - 1 == room->get_r())
						if (find_path(room->get_r(), c))
							return true;
					if (c + 1 == room->get_c())
						if (find_path(r, room->get_c()))
							return true;
					if (c - 1 == room->get_c())
						if (find_path(r, room->get_c()))
							return true;
				}
			}


		}
		maze[r][c].set_current_path(false);
		maze[r][c].set_old_path(true);
		return false;

	}
	else return true;

}