#pragma once
#include <iostream>
class Room
{
	bool wall;
	bool visited;
	bool path;
	bool old_path;
	int r;
	int c;

public:
	Room();
	~Room();
	bool is_wall();
	bool is_visited();
	void set_visited();
	void set_unvisited();
	void set_wall();
	void set_path();
	int get_r();
	int get_c();
	void set_c(int);
	void set_r(int);
	void mark_path();
	void clear_path();
	void set_current_path(bool);
	void set_old_path(bool);
	friend std::ostream&  operator << (std::ostream&, const Room&);
};

