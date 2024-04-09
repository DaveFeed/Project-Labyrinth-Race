#pragma once
#include "Labyrinth.h"

class Player
{
public:
    Player();
    Player(std::pair<int, int> pos);
    Player(int x, int y);

    virtual void move(const Labyrinth& labyrinth) = 0;
    virtual void draw();
    std::pair<int, int> get_pos();
    void clear_pos();

    void kill();

protected:
    std::pair<int, int> pos;
    std::pair<int, int> prev_pos;
    char sprite = 0;
    bool is_dead = false;
};