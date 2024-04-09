#pragma once
#include "Labyrinth.h"

class Player
{
public:
    Player(std::pair<int, int> pos, Labyrinth& labyrinth);
    Player(int x, int y, Labyrinth& labyrinth);

    virtual void move() = 0;
    virtual void draw() = 0;
    std::pair<int, int> get_pos();
    void clear_pos();

    void kill();

protected:
    Labyrinth& labyrinth;
    std::pair<int, int> pos;
    std::pair<int, int> prev_pos;
    char sprite = 0;
    bool is_dead = false;
};