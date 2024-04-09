#pragma once
#include <set>
#include "Labyrinth.h"
#include "Player.h"

class Fire {
public:
    Fire(Labyrinth& labyrinth);

    void update();
    void draw();
    void set_pos(std::pair<int, int> pos);

    std::set<std::pair<int, int>> get_fire_pos() const;

private:
    Labyrinth& labyrinth;
    std::set<std::pair<int, int>> fire_pos;
    char sprite = '@';
};