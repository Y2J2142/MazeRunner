#include "stdafx.h"
#include "Room.h"
#include <cstdlib>
#include <windows.h>


Room::Room()
{
	wall = visited = path = old_path = false;
}


Room::~Room()
{
}

bool Room::is_visited()
{
	return visited;
}


void Room::set_visited()
{
	visited = true;
}
void Room::set_unvisited()
{
	visited = false;
}

bool Room::is_wall()
{
	return wall;
}

void Room::set_wall()
{
	wall = true;
}

void Room::set_path()
{
	wall = false;
}

int Room::get_r()
{
	return r;
}
int Room::get_c()
{
	return c;
}

void Room::set_r(int rr)
{
	r = rr;
}

void Room::set_c(int cc)
{
	c = cc;
}

void Room::mark_path()
{
	path = true;
}

void Room::clear_path()
{
	path = false;
}

void Room::set_current_path(bool p)
{
	path = p;
}

void Room::set_old_path(bool p)
{
	old_path = p;
}
std::ostream & operator<<(std::ostream & o, const Room & r)
{
	
	
	if (r.old_path)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		o << (char)219;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (r.path)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		o << (char)219;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	}
	else
	{
		if (r.wall)
			o << (char)219;
		else
			o << " ";

	}
	return o;
}