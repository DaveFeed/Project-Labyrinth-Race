#pragma once
#include <vector>
#include <cstdlib> //for rand(), srand()
#include <ctime>   //for time() to use srand(time(NULL))
#include <stack>   //std::stack for dfs in labyrinth construcing
#include <iostream>

class Labyrinth
{
public:
    //A constructor that sets height and width of maze(default is 20x20)
    Labyrinth (unsigned height = 20, unsigned width = 20);

    void init();
    void draw();

private:
    unsigned height;
    unsigned width;
    std::vector<std::vector<int>> labyrinth;

    // '|' and '&' bitwise operators will be used to check if vertex has pathes(0101 - has north and east paths)
    enum {
        UP_PATH = 1,
        BOTTOM_PATH = 2,
        RIGHT_PATH = 4,
        LEFT_PATH = 8,
    };
};