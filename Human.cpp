#include <iostream>
#include <cstdlib>

#include "Human.h"
#include "Helpers.h"

Human::Human(std::pair<int, int> pos, Labyrinth& labyrinth) : Player(pos, labyrinth) {
    sprite = '$';
    Helpers::nonblock(0);
}

Human::Human(int x, int y, Labyrinth& labyrinth) : Player(std::make_pair(x, y), labyrinth) {
    sprite = '$';
    Helpers::nonblock(0);
}

Human::~Human() {
    Helpers::nonblock(1);
}

void Human::move() {
    prev_pos = pos;
    labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::EMPTY;
    do {
        key_pressed = Helpers::read_char();
        std::cout << "\r \r";
        switch(key_pressed) {
            case KEYS::w:
                if(!labyrinth.is_wall(pos.first, pos.second - 1)) {
                    pos.second -= 2;
                    return;
                }

                if (labyrinth.is_exit(pos.first, pos.second - 1)) {
                    pos.second -= 1;
                    return;
                }
                break;

            case KEYS::a:
                if(!labyrinth.is_wall(pos.first - 1, pos.second)) {
                    pos.first -= 2;
                    return;
                }

                if (labyrinth.is_exit(pos.first - 1, pos.second)) {
                    pos.first -= 1;
                    return;
                }
                break;

            case KEYS::s:
                if(!labyrinth.is_wall(pos.first, pos.second + 1)) {
                    pos.second += 2;
                    return;
                }

                if (labyrinth.is_exit(pos.first, pos.second + 1)) {
                    pos.second += 1;
                    return;
                }
                break;

            case KEYS::d:
                if(!labyrinth.is_wall(pos.first + 1, pos.second)) {
                    pos.first += 2;
                    return;
                }

                if (labyrinth.is_exit(pos.first + 1, pos.second)) {
                    pos.first += 1;
                    return;
                }
                break;
            case KEYS::q:
                Helpers::clear();
                exit(0);
            default:
                break;
        }
    } while (true);
    labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::HUMAN;
}

void Human::draw() {
	if(is_dead) return;
    clear_pos();
	labyrinth.get_lab()[pos.first][pos.second] = TILE_TYPES::HUMAN;
	Helpers::draw_char_at(pos, sprite);
    Helpers::drop_cursor();
}