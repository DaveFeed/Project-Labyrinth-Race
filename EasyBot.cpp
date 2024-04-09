#include <iostream>
#include <cstdlib>

#include "EasyBot.h"
#include "Helpers.h"

EasyBot::EasyBot(std::pair<int, int> pos, Labyrinth& labyrinth) : Player(pos, labyrinth) { sprite = 'E'; };
EasyBot::EasyBot(int x, int y, Labyrinth& labyrinth) : Player(x, y, labyrinth) { sprite = 'E'; };

void EasyBot::move() {
	prev_pos = pos;
	if (is_dead) return;
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::EMPTY;
	int tries = 4;
	direction = rand() % 4;

	do {
		switch (direction) {
		case 0:
			if (labyrinth.get_lab()[pos.first][pos.second - 1] != TILE_TYPES::WALL 
				&& labyrinth.get_lab()[pos.first][pos.second - 2] != TILE_TYPES::FIRE) {
				pos.second -= 2;
				tries = 0;
				break;
			}

			if (labyrinth.get_lab()[pos.first][pos.second - 1] == TILE_TYPES::EXIT) {
				pos.second -= 1;
				tries = 0;
				break;
			}
			break;
		case 1:
			if (labyrinth.get_lab()[pos.first - 1][pos.second] != TILE_TYPES::WALL 
				&& labyrinth.get_lab()[pos.first - 2][pos.second] != TILE_TYPES::FIRE) {
				pos.first -= 2;
				tries = 0;
				break;
			}

			if (labyrinth.get_lab()[pos.first - 1][pos.second] == TILE_TYPES::EXIT) {
				pos.first -= 1;
				tries = 0;
				break;
			}
			break;
		case 2:
			if (labyrinth.get_lab()[pos.first][pos.second + 1] != TILE_TYPES::WALL 
				&& labyrinth.get_lab()[pos.first][pos.second + 2] != TILE_TYPES::FIRE) {
				pos.second += 2;
				tries = 0;
				break;
			}

			if (labyrinth.get_lab()[pos.first][pos.second + 1] == TILE_TYPES::EXIT) {
				pos.second += 1;
				tries = 0;
				break;
			}
			break;
		case 3:
			if (labyrinth.get_lab()[pos.first + 1][pos.second] != TILE_TYPES::WALL 
				&& labyrinth.get_lab()[pos.first + 2][pos.second] != TILE_TYPES::FIRE) {
				pos.first += 2;
				tries = 0;
				break;
			}

			if (labyrinth.get_lab()[pos.first + 1][pos.second] == TILE_TYPES::EXIT) {
				pos.first += 1;
				tries = 0;
				break;
			}
			break;
		}
		--tries;
		direction = (direction + 1) % 4;
	} while (tries > 0);
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
}

void EasyBot::draw() {
	if(is_dead) return;
	clear_pos();
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
	Helpers::draw_char_at(pos, sprite);
    Helpers::drop_cursor();
}