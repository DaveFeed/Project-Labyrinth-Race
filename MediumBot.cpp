#include <iostream>
#include <cstdlib>

#include "MediumBot.h"
#include "Helpers.h"

MediumBot::MediumBot(std::pair<int, int> pos, Labyrinth& labyrinth) : Player(pos, labyrinth) { 
    sprite = 'M';
    where_to_turn = rand() % labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] + 1;
};
MediumBot::MediumBot(int x, int y, Labyrinth& labyrinth) : Player(x, y, labyrinth) { 
    sprite = 'M';
    where_to_turn = rand() % (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1) + 1;
};

void MediumBot::move() {
	if (is_dead) return;
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::EMPTY;
    --where_to_turn;
    if(where_to_turn == -1 || where_to_turn == -2) {
        auto temp = pos;
        pos = prev_pos;
        prev_pos = temp;
        labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
        return;
    }
	prev_pos = pos;

    bool moved = false;
    direction = 0;
    while(!moved) {
        switch(direction) {
            case 0:
                if(labyrinth.get_weight_map()[pos.first / 2][(pos.second - 2) / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first][pos.second - 1] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.second -= 2;
                }
                if(labyrinth.get_lab()[pos.first][pos.second - 1] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.second -= 1;
                }
            break;
            case 1:
                if(labyrinth.get_weight_map()[(pos.first - 2) / 2][pos.second / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first - 1][pos.second] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.first -= 2;
                }
                if(labyrinth.get_lab()[pos.first - 1][pos.second] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.first -= 1;
                }
            break;
            case 2:
                if(labyrinth.get_weight_map()[pos.first / 2][(pos.second + 2) / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first][pos.second + 1] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.second += 2;
                }
                if(labyrinth.get_lab()[pos.first][pos.second + 1] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.second += 1;
                }
            break;
            case 3:
                if(labyrinth.get_weight_map()[(pos.first + 2) / 2][pos.second / 2] == (labyrinth.get_weight_map()[pos.first / 2][pos.second / 2] - 1)
                   && labyrinth.get_lab()[pos.first + 1][pos.second] != TILE_TYPES::WALL) {
                    moved = true;
                    pos.first += 2;
                }
                if(labyrinth.get_lab()[pos.first + 1][pos.second] == TILE_TYPES::EXIT) {
                    moved = true;
                    pos.first += 1;
                }
            break;
        }
        ++direction;
    }
	
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
}

void MediumBot::draw() {
	if(is_dead) return;
	clear_pos();
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::BOT;
	Helpers::draw_char_at(pos, sprite);
    Helpers::drop_cursor();
}