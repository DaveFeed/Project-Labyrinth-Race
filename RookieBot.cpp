#include <iostream>
#include <cstdlib>

#include "RookieBot.h"
#include "Helpers.h"

RookieBot::RookieBot(std::pair<int, int> pos, Labyrinth& labyrinth) : Player(pos, labyrinth){ sprite = 'R'; };
RookieBot::RookieBot(int x, int y, Labyrinth& labyrinth) : Player(x, y, labyrinth){ sprite = 'R'; };

void RookieBot::move() {
	prev_pos = pos;
	if (is_dead) return;
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::EMPTY;
	bool moved = false;

	do {
		direction = rand() % 4;
		switch (direction) {
		case UP:
			if (labyrinth.is_exit(pos.first, pos.second - 1)) {
				pos.second -= 1;
				moved = true;
				break;
			}

			if (!labyrinth.is_wall(pos.first, pos.second - 1) && pos.second > 1) {
				pos.second -= 2;
				moved = true;
				break;
			}
			break;
		case LEFT:
			if (labyrinth.is_exit(pos.first - 1, pos.second)) {
				pos.first -= 1;
				moved = true;
				break;
			}

			if (!labyrinth.is_wall(pos.first - 1, pos.second) && pos.first > 1) {
				pos.first -= 2;
				moved = true;
				break;
			}
			break;
		case DOWN:
			if (labyrinth.is_exit(pos.first, pos.second + 1)) {
				pos.second += 1;
				moved = true;
				break;
			}

			if (!labyrinth.is_wall(pos.first, pos.second + 1) && pos.second < labyrinth.get_labyrinth_size().second - 2) {
				pos.second += 2;
				moved = true;
				break;
			}
			break;
		case RIGHT:
			if (labyrinth.is_exit(pos.first, pos.second + 1)) {
				pos.second += 1;
				moved = true;
				break;
			}

			if (!labyrinth.is_wall(pos.first + 1, pos.second) && pos.first < labyrinth.get_labyrinth_size().first - 2) {
				pos.first += 2;
				moved = true;
				break;
			}
			break;
		}
	} while (!moved);
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
}

void RookieBot::draw() {
	if(is_dead)  {
		if(labyrinth.get_lab()[pos.first][pos.first] != TILE_TYPES::FIRE)
		prev_pos = pos;
		clear_pos();
		return;
	}
	clear_pos();
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
	Helpers::draw_char_at(pos, sprite);
    Helpers::drop_cursor();
}