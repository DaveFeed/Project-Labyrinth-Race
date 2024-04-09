#include "HardBot.h"
#include "Helpers.h"

#include <iostream>
#include <cstdlib>

HardBot::HardBot(std::pair<int, int> pos, Labyrinth& labyrinth) : Player(pos, labyrinth) { 
    sprite = 'H';
};
HardBot::HardBot(int x, int y, Labyrinth& labyrinth) : Player(x, y, labyrinth) { 
    sprite = 'H';
};

void HardBot::move() {
	prev_pos = pos;
	if (is_dead) return;
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::EMPTY;

    bool moved = false;
    direction = 0;
    while(!moved) {
        switch(direction) {
            case 0:
                if(labyrinth.get_lab()[pos.first][pos.second - 1] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.second -= 1;
                    break;
                }
                if(labyrinth.get_weight_map()[pos.first / 2][(pos.second - 2) / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first][pos.second - 1] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.second -= 2;
                }
            break;
            case 1:
                if(labyrinth.get_lab()[pos.first - 1][pos.second] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.first -= 1;
                    break;
                }
                if(labyrinth.get_weight_map()[(pos.first - 2) / 2][pos.second / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first - 1][pos.second] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.first -= 2;
                }
            break;
            case 2:
                if(labyrinth.get_lab()[pos.first][pos.second + 1] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.second += 1;
                    break;
                }
                if(labyrinth.get_weight_map()[pos.first / 2][(pos.second + 2) / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first][pos.second + 1] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.second += 2;
                }
            break;
            case 3:
                if(labyrinth.get_lab()[pos.first + 1][pos.second] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.first += 1;
                    break;
                }
                if(labyrinth.get_weight_map()[(pos.first + 2) / 2][pos.second / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first + 1][pos.second] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.first += 2;
                }
            break;
        }
        ++direction;
    }
	
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
}

void HardBot::draw() {
	if(is_dead) return;
	clear_pos();
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
	Helpers::draw_char_at(pos, sprite);
    Helpers::drop_cursor();
}