#pragma once
#include <iostream>
#include <cstdlib>

#include "EasyBot.h"
#include "Player.h"
#include "Helpers.h"

EasyBot::EasyBot() { sprite = 'E'; };
EasyBot::EasyBot(std::pair<int, int> pos) : Player(pos) { sprite = 'E'; };
EasyBot::EasyBot(int x, int y) : Player(x, y) { sprite = 'E'; };

void EasyBot::move(const Labyrinth& labyrinth) {
	prev_pos = pos;
	if (is_dead) return;

	do {
		direction = rand() % 4;
		switch (direction) {
		case UP:
			if (!labyrinth.is_wall(pos.first, pos.second - 1) && pos.second > 1) {
				pos.second -= 2;
				return;
			}

			if (labyrinth.is_exit(pos.first, pos.second - 1)) {
				pos.second -= 1;
				return;
			}
			break;
		case LEFT:
			if (!labyrinth.is_wall(pos.first - 1, pos.second) && pos.first > 1) {
				pos.first -= 2;
				return;
			}

			if (labyrinth.is_exit(pos.first - 1, pos.second)) {
				pos.first -= 1;
				return;
			}
			break;
		case DOWN:
			if (!labyrinth.is_wall(pos.first, pos.second + 1) && pos.second < labyrinth.get_labyrinth_size().second - 2) {
				pos.second += 2;
				return;
			}

			if (labyrinth.is_exit(pos.first, pos.second + 1)) {
				pos.second += 1;
				return;
			}
			break;
		case RIGHT:
			if (!labyrinth.is_wall(pos.first + 1, pos.second) && pos.first < labyrinth.get_labyrinth_size().first - 2) {
				pos.first += 2;
				return;
			}

			if (labyrinth.is_exit(pos.first, pos.second + 1)) {
				pos.second += 1;
				return;
			}
			break;
		}
	} while (true);
}
