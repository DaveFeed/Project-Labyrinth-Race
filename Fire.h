#pragma once
#include <set>
#include "Labyrinth.h"
#include "Player.h"

class Fire {
public:
    Fire();
    Fire(int amount);

    void update(const Labyrinth& labyrinth);
    void draw();
    void set_pos(std::pair<int, int> pos, const Labyrinth& labyrinth);

    std::set<std::pair<int, int>> get_fire_pos() const;

private:
    int amount = 1;
    std::set<std::pair<int, int>> fire_pos;
    char sprite = '*';
};