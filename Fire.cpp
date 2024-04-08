#include "Fire.h"

Fire::Fire(int amount):amount(amount){}

void Fire::set_fire(std::pair<int, int> pos) {
    fire_pos.insert(pos);
}

void Fire::spread_fire(const Labyrinth& labyrinth) {
    std::vector<std::pair<int, int>> to_add;
    for(auto it: fire_pos) {
        int x = it.first;
        int y = it.second;
        if(!labyrinth.is_wall(x - 1, y)) {
            to_add.emplace_back(x-2, y);
        }
        if(!labyrinth.is_wall(x + 1,y)) {
            to_add.emplace_back(x+2, y);
        }
        if(!labyrinth.is_wall(x, y - 1)) {
            to_add.emplace_back(x, y-2);
        }
        if(!labyrinth.is_wall(x, y + 1)) {
            to_add.emplace_back(x, y+2);
        }
    }
    for(auto pair: to_add) {
        fire_pos.insert(pair);
    }
}

void Fire::draw() {
    for(auto pair: fire_pos) {
        std::cout << "\x1B[" << pair.second + 1 << ";" << pair.first + 1 << "f";
        std::cout << '*';
    }
    std::cout << "\x1B[" << 50 << ";" << 1 << "f";
}