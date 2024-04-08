#pragma once
#include "Labyrinth.h"

class Player
{
public:
    Player();
    Player(std::pair<int, int> pos);
    Player(int x, int y);

    virtual bool move(const Labyrinth& labyrinth) = 0;                    //returns true if won(maybe?)
    std::pair<int, int> get_pos();
    void set_pos(std::pair<int, int> pos);
    void set_pos(int x, int y);
    void clear_pos();

protected:
    std::pair<int, int> pos;
    std::pair<int, int> prev_pos;
};