#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game() 
:labyrinth(6, 6, 2)
,ui()
,fire(1)
{
	srand(time(NULL));
	difficulty = DIFFICULTY::Rookie;
}

std::pair<int, int> Game::find_position(int distance) {
	auto weight_map = labyrinth.get_weight_map();
	int x = rand() % weight_map.size();
	int y = rand() % weight_map[0].size();
	while(weight_map[x][y] != distance) {
		int new_x = x, new_y = y;
		if(x > 0) {
			if(abs(weight_map[x - 1][y] - distance) < abs(weight_map[new_x][new_y] - distance)) {
				new_x = x - 1;
				new_y = y;
			}
		}
		if(x < weight_map.size() - 1) {
			if(abs(weight_map[x + 1][y] - distance) < abs(weight_map[new_x][new_y] - distance)) {
				new_x = x + 1;
				new_y = y;
			}
		}
		if(y > 0) {
			if(abs(weight_map[x][y - 1] - distance) < abs(weight_map[new_x][new_y] - distance)) {
				new_x = x;
				new_y = y - 1;
			}
		}
		if(y < weight_map[0].size() - 1) {
			if(abs(weight_map[x][y + 1] - distance) < abs(weight_map[new_x][new_y] - distance)) {
				new_x = x;
				new_y = y + 1;
			}
		}
		if((x == new_x) && (y == new_y)) {
			x = rand() % weight_map.size();
			y = rand() % weight_map[0].size();
		}
		else {
			x = new_x;
			y = new_y;
		}
	}
	x = 2 * x + 1;
	y = 2 * y + 1;
	return std::make_pair(x, y);
}

void Game::start() {
	labyrinth.init();

	int distance = rand() % (labyrinth.get_max() * 3 / 4);
	while(distance <= (labyrinth.get_min() / 4)) {
		distance += (labyrinth.get_min() / 4);
	}
	player.set_pos(find_position(distance));
	bot.set_pos(find_position(distance));

	distance += (labyrinth.get_min() / 2);
	fire.set_fire(find_position(distance));

	labyrinth.draw();
	player.draw();
	bot.draw();
	fire.draw();
	game_loop();
}

void Game::game_loop() {
	while(true) {
		if(!player.move(labyrinth)) {
			break;
		}
		bot.move(labyrinth);
		fire.spread_fire(labyrinth);

		player.clear_pos();
		player.draw();

		bot.clear_pos();
		bot.draw();

		fire.draw();
	}
}