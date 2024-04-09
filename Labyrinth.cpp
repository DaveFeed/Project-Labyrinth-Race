#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <climits>
#include <algorithm>

#include "Labyrinth.h"
#include "Helpers.h"

Labyrinth::Labyrinth(unsigned height, unsigned width, int exits_count) :
	room_height(height)
	, room_width(width)
	, vec_height(height * 2 + 1)
	, vec_width(width * 2 + 1)
	, labyrinth(vec_width, std::vector<int>(vec_height, TILE_TYPES::WALL))
	, weight_map(room_width, std::vector<int>(room_height, 1e6))
	, exits_count(exits_count)
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
	int walls = (vec_height - 2) * (vec_width - 2) - (room_height - 1) * (room_width - 1) - 1;

	int x = (rand() % 2 * room_width);
	if (x % 2 == 0) {
		++x;
	}

	int y = (rand() % 2 * room_height);
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
	for (int y = 0; y < vec_height; ++y) {
		for (int x = 0; x < vec_width; ++x) {
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
	std::vector<std::vector<bool>> visited(room_width, std::vector<bool>(room_height, false));
	std::vector<std::vector<int>> distances(room_width, std::vector<int>(room_height));

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

			if (x >= 0 && x < room_width && y >= 0 && y < room_height &&
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

		for (unsigned x = 0; x < room_width; ++x)
		{
			for (unsigned y = 0; y < room_height; ++y)
			{
				weight_map[x][y] = std::min(weight_map[x][y], exitBfs[x][y]);
			}
		}
	}
}

// This name is not it Rafo and i dont care to change it
bool Labyrinth::is_wall(int x, int y) const {
	return labyrinth[x][y] != TILE_TYPES::EMPTY;
}

bool Labyrinth::is_wall(std::pair<int, int> pos) const {
	return labyrinth[pos.first][pos.second] != TILE_TYPES::EMPTY;
}

bool Labyrinth::is_exit(int x, int y) const {
	return labyrinth[x][y] == TILE_TYPES::EXIT;
}

bool Labyrinth::is_exit(std::pair<int, int> pos) const {
	return labyrinth[pos.first][pos.second] != TILE_TYPES::EXIT;
}

std::vector<std::vector<int>> Labyrinth::get_weight_map() const {
	return weight_map;
}

std::vector<std::pair<int, int>> Labyrinth::get_exits() const {
	return exits;
}

int Labyrinth::get_min() {
	// todo:: (refactor) hard coded, can be changed to some height/width calculations
	// not used currently
	return 5;
}

int Labyrinth::get_max() {
	int max_num = weight_map[0][0];

	for (const auto& row : weight_map) {
		for (int num : row) {
			if (num > max_num) {
				max_num = num;
			}
		}
	}

	return max_num;
}

// First is player, second is bot, third is fire
std::vector<std::pair<int, int>> Labyrinth::generate_positions(int fire_amount) {
	// distance: vector of coordinates
	std::unordered_map<int, std::vector<std::pair<int, int>>> count_map;
	std::vector<std::pair<int, int>> res;

	// todo:: (refactor) hard coded number
	int max_num = get_max();
	int max_calculation_num = max_num - 5;

	for (size_t x = 0; x < room_width; ++x) {
		for (size_t y = 0; y < room_height; ++y) {
			count_map[weight_map[x][y]].push_back(std::make_pair(2 * x + 1, 2 * y + 1));
		}
	}

	int pair_num = INT_MIN;
	for (const auto& pair : count_map) {
		if (pair.second.size() >= 2 && pair.first < max_calculation_num && pair.first > pair_num) {
			pair_num = pair.first;
		}
	}

	std::random_shuffle(count_map[pair_num].begin(), count_map[pair_num].end());
	std::random_shuffle(count_map[max_num].begin(), count_map[max_num].end());
	std::random_shuffle(count_map[max_num - 1].begin(), count_map[max_num - 1].end());
	std::random_shuffle(count_map[max_num - 2].begin(), count_map[max_num - 2].end());
	res.push_back(count_map[pair_num][0]);
	res.push_back(count_map[pair_num][1]);
	for(int i = 0; i < fire_amount; ++i) {
		res.push_back(count_map[max_num - i][0]);
	}


	return res; // std::vector<std::pair<int, int>>{count_map[pair_num][0], count_map[pair_num][1], count_map[max_num][0]};
}

void Labyrinth::draw_wm() {
	for (unsigned j = 0; j < room_height; ++j) {
		for (unsigned i = 0; i < room_width; ++i) {
			std::cout << weight_map[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

std::pair<int,int> Labyrinth::get_labyrinth_size() const {
	return std::make_pair(vec_width, vec_height);
}

std::vector<std::vector<int>>& Labyrinth::get_lab() {
	return labyrinth;
}