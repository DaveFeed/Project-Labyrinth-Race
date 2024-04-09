#pragma once
#include "Player.h"

class EasyBot :
    public Player
{
public:
    EasyBot(std::pair<int, int> pos, Labyrinth& labyrinth);
    EasyBot(int x, int y, Labyrinth& labyrinth);

    void move() override;
    void draw() override;

private:
    enum DIRS {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };
    int direction = 0;
};