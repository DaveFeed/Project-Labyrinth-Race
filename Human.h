#pragma once
#include "Player.h"

class Human: public Player
{
public:
    Human();
    Human(std::pair<int, int> pos);
    Human(int x, int y);
    ~Human();

    void move(const Labyrinth& labyrinth) override;

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