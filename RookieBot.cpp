#include "RookieBot.h"
#include <iostream>
#include <cstdlib>

RookieBot::RookieBot(){}

RookieBot::RookieBot(std::pair<int, int> pos): Player(pos) {
}

RookieBot::RookieBot(int x, int y): Player(std::make_pair(x, y)) {
}

bool RookieBot::move(const Labyrinth& labyrinth) {
    prev_pos = pos;
    bool moved = false;
    while(!moved) {
        direction = rand() % 4;
        switch(direction) {
        case UP:
            if(!labyrinth.is_wall(pos.first, pos.second - 1)) {
                pos.second -= 2;
                moved = true;
            }
        break;
        case LEFT:
            if(!labyrinth.is_wall(pos.first - 1, pos.second)) {
                pos.first -= 2;
                moved = true;
            }
        break;
        case DOWN:
            if(!labyrinth.is_wall(pos.first, pos.second + 1)) {
                pos.second += 2;
                moved = true;
            }
        break;
        case RIGHT:
            if(!labyrinth.is_wall(pos.first + 1, pos.second)) {
                pos.first += 2;
                moved = true;
            }
        break;
        }
    }
    return true;
}

void RookieBot::draw() {
    std::cout << "\x1B[" << pos.second + 1 << ";" << pos.first + 1 << "f";
    std::cout << '@';
    std::cout << "\x1B[" << 50 << ";" << 1 << "f";
}