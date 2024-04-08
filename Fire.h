#pragma once
#include <set>
#include "Labyrinth.h"

class Fire {
public:
    Fire(int amount);
    void set_fire(std::pair<int, int> pos);
    void spread_fire(const Labyrinth& labyrinth);
    void draw();

private:
    int amount;
    std::set<std::pair<int, int>> fire_pos;
};