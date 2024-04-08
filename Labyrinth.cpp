#include "Labyrinth.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

Labyrinth::Labyrinth(unsigned height, unsigned width) :
	rooms_height(height)
	, rooms_width(width)
	, vec_height(rooms_height * 2 + 1)
	, vec_width(rooms_width * 2 + 1)
	, labyrinth(vec_width, std::vector<int>(vec_height, TILE_TYPES::WALL))
	, weight_map(rooms_width, std::vector<int>(rooms_height, 1e6))
	, exits_count(2)
	, exits()
{
}

void Labyrinth::init()
{
	labyrinth[0][0] = TILE_TYPES::WALL_INTERSECT;
	labyrinth[0][vec_height - 1] = TILE_TYPES::WALL_INTERSECT;
	labyrinth[vec_width - 1][0] = TILE_TYPES::WALL_INTERSECT;
	labyrinth[vec_width - 1][vec_height - 1] = TILE_TYPES::WALL_INTERSECT;

	for (int i = 2; i < vec_width - 1; i += 2) {
		for (int j = 2; j < vec_height - 1; j += 2) {
			labyrinth[i][j] = TILE_TYPES::WALL_INTERSECT;
		}
	}

	std::stack<std::pair<int, int>> st;
	int walls = (vec_height - 2) * (vec_width - 2) - (rooms_height - 1) * (rooms_width - 1) - 1;
	int rooms = 1;

	int x = (rand() % 2 * rooms_width);
	if (x % 2 == 0) {
		++x;
	}

	int y = (rand() % 2 * rooms_height);
	if (y % 2 == 0) {
		++y;
	}

	st.push(std::make_pair(x, y));

	while (!st.empty()) {
		labyrinth[x][y] = 0;
		std::vector<std::pair<int, int>> neighs;

		if (x > 1) {
			if (labyrinth[x - 2][y] == 1) {
				neighs.push_back(std::make_pair(x - 2, y));
			}
		}
		if (x < vec_width - 2) {
			if (labyrinth[x + 2][y] == 1) {
				neighs.push_back(std::make_pair(x + 2, y));
			}
		}
		if (y > 1) {
			if (labyrinth[x][y - 2] == 1) {
				neighs.push_back(std::make_pair(x, y - 2));
			}
		}
		if (y < vec_height - 2) {
			if (labyrinth[x][y + 2] == 1) {
				neighs.push_back(std::make_pair(x, y + 2));
			}
		}

		if (!neighs.empty()) {
			int neighbor = rand() % neighs.size();
			int new_x = neighs[neighbor].first;
			int new_y = neighs[neighbor].second;

			labyrinth[(x + new_x) / 2][(y + new_y) / 2] = TILE_TYPES::EMPTY;
			walls -= 2;
			++rooms;
			x = new_x;
			y = new_y;
			st.push(std::make_pair(x, y));
		}
		else {
			st.pop();

			if (!st.empty()) {
				x = st.top().first;
				y = st.top().second;
			}
		}
	}

	addLoops(walls);

	addExits();

	generateWeightMap();
}

void Labyrinth::draw()
{
	for (int y = 0; y < vec_width; ++y) {
		for (int x = 0; x < vec_height; ++x) {
			switch (labyrinth[x][y])
			{
			case TILE_TYPES::EMPTY:
				std::cout << ' ';
				break;
			case TILE_TYPES::WALL:
				if (x == 0 || x == vec_width - 1 || y % 2 != 0) {
					std::cout << '|';
				}
				else {
					std::cout << '-';
				}
				break;
			case TILE_TYPES::WALL_INTERSECT:
				std::cout << '+';
				break;
			case TILE_TYPES::EXIT:
				std::cout << '#';
				break;
			default:
				break;
			}
		}

		std::cout << std::endl;
	}
}

void Labyrinth::addLoops(int walls) {
	for (int i = 0; i < walls / 3; ++i) {
		while (true) {
			int x = rand() % (vec_width - 2) + 1;
			int y = rand() % (vec_height - 2) + 1;

			if (x % 2 == 0) {
				if (y % 2 == 0) {
					y = y + 1;
				}
			}
			else {
				while (y % 2 != 0) {
					y = (y + 1) % (vec_width - 2);
				}
			}

			if (labyrinth[x][y] == TILE_TYPES::WALL) {
				labyrinth[x][y] = TILE_TYPES::EMPTY;
				break;
			}
		}
	}
}

void Labyrinth::addExits() {
	int x = 0;
	int y = 0;
	int side;

	enum
	{
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};

	while (exits_count > 0)
	{
		side = rand() % 4;
		switch (side)
		{
		case TOP:
			x = (rand() % (vec_width - 2)) + 1;
			if (x % 2 == 0) {
				++x;
			}
			y = 0;
			break;
		case RIGHT:
			x = vec_width - 1;
			y = (rand() % (vec_height - 2)) + 1;
			if (y % 2 == 0) {
				++y;
			}
			break;
		case BOTTOM:
			x = (rand() % (vec_width - 2)) + 1;
			if (x % 2 == 0) {
				++x;
			}
			y = vec_height - 1;
			break;
		case LEFT:
			x = 0;
			y = (rand() % (vec_height - 2)) + 1;
			if (y % 2 == 0) {
				++y;
			}
			break;
		}

		bool retry = false;
		for (auto ex : exits) {
			if (abs(ex.first - x) + abs(ex.second - y) < std::min(vec_height, vec_width) / 2) {
				retry = true;
				break;
			}
		}

		if (retry) continue;

		exits.push_back(std::make_pair(x, y));
		labyrinth[x][y] = TILE_TYPES::EXIT;
		--exits_count;
	}
}

std::vector<std::vector<int>> Labyrinth::bfs(std::pair<int, int> exitPos)
{
	std::vector<std::vector<bool>> visited(rooms_width, std::vector<bool>(rooms_height, false));
	std::vector<std::vector<int>> distances(rooms_width, std::vector<int>(rooms_height));

	std::queue<std::pair<int, int>> q;

	// get closest point on map to exit location
	if (exitPos.first == vec_width - 1) { // right side
		exitPos.first -= 1;
	}
	else if (exitPos.second == vec_height - 1) { // bottom side
		exitPos.second -= 1;
	}

	int start_x = exitPos.first / 2;
	int start_y = exitPos.second / 2;

	q.push({ start_x, start_y });
	visited[start_x][start_y] = true;
	distances[start_x][start_y] = 1;

	std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

	while (!q.empty())
	{
		std::pair<int, int> current = q.front();
		q.pop();

		for (const auto& dir : directions)
		{
			int x = current.first + dir.first;
			int y = current.second + dir.second;

			if (x >= 0 && x < rooms_width && y >= 0 && y < rooms_height &&
				!visited[x][y] && labyrinth[current.first * 2 + 1 + dir.first][current.second * 2 + 1 + dir.second] == TILE_TYPES::EMPTY)
			{
				visited[x][y] = true;
				distances[x][y] = distances[current.first][current.second] + 1;
				q.push({ x, y });
			}
		}
	}

	return distances;
}

void Labyrinth::generateWeightMap()
{
	for (const auto& exit : exits)
	{
		const auto exitBfs = bfs(exit);

		for (int x = 0; x < rooms_width; ++x)
		{
			for (int y = 0; y < rooms_height; ++y)
			{
				weight_map[x][y] = std::min(weight_map[x][y], exitBfs[x][y]);
			}
		}
	}
}
