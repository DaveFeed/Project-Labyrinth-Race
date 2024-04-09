#pragma once
#include "Player.h"

class Human: public Player
{
public:
    Human(std::pair<int, int> pos, Labyrinth& labyrinth);
    Human(int x, int y, Labyrinth& labyrinth);
    ~Human();

    void move() override;
    void draw() override;

private:
    enum KEYS {
        w = 119,
        a = 97,
        s = 115,
        d = 100,
        q = 113
    };

    char key_pressed = 0;
};