#pragma once
#include <iostream>
#include <cstdlib>

#include "Human.h"
#include "Helpers.h"

Human::Human() {     //to avoid code duplication created default constructor, 
    sprite = '$';
    Helpers::nonblock(0);        //but error occured(delegation with mem-initialization)
}

Human::Human(std::pair<int, int> pos) : Player(pos) {
    sprite = '$';
    Helpers::nonblock(0);
}

Human::Human(int x, int y) : Player(std::make_pair(x, y)) {
    sprite = '$';
    Helpers::nonblock(0);
}

Human::~Human() {
    Helpers::nonblock(1);
}

void Human::move(const Labyrinth& labyrinth) {
    prev_pos = pos;

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
                exit(0);
            default:
                break;
        }
    } while (true);
}
