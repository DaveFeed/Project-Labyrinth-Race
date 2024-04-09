#pragma once
#include "Player.h"

class MediumBot :
    public Player
{
public:
    MediumBot(std::pair<int, int> pos, Labyrinth& labyrinth);
    MediumBot(int x, int y, Labyrinth& labyrinth);

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
    int where_to_turn;
};