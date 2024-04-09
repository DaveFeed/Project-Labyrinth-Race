#pragma once
#include "Player.h"

class EasyBot :
    public Player
{
public:
    EasyBot();
    EasyBot(std::pair<int, int> pos);
    EasyBot(int x, int y);

    void move(const Labyrinth& labyrinth) override;

private:
    enum DIRS {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };
    int direction = 0;
};
