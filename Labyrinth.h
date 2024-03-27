#pragma once
#include <vector>
#include <iostream>

class Labyrinth
{
public:
	Labyrinth(unsigned height = 20, unsigned width = 20);

	enum TILE_TYPES : char {
		EMPTY = 0,
		WALL = 1,
		PLAYER = 2,
		BOT = 3,
		FIRE = 4
	};

	void init();
	void checkAvailable(int x, int y);
	void update(); // todo::

	// todo:: (refactor) bad practice
	std::vector<std::vector<int>> data;
private:
	unsigned height;
	unsigned width;

	// todo:: (remove)
	enum PATHS {
		UP = 0b0001,
		DOWN = 0b0010,
		RIGHT = 0b0100,
		LEFT = 0b1000,
	};
};


