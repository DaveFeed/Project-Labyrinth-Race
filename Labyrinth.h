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
		FIRE = 4,
		EXIT = 5
	};

	void init();
	void checkAvailable(int x, int y);
	void update(); // todo::
	void createWeightMap();

	// todo:: (refactor) bad practice
	std::vector<std::vector<int>> labyrinth;
	std::vector<std::vector<int>> weightMap;
	std::vector<std::pair<int,int>> exits;
private:
	unsigned height;
	unsigned width;

	void addPaths();
	void addLoops(unsigned short count);
	void addExits(unsigned short count);
	std::vector<std::vector<int>> bfs(std::pair<int,int> startPoint);
};


