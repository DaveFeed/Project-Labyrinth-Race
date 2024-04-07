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
    unsigned rooms_height;
    unsigned rooms_width;
    unsigned vec_height;
    unsigned vec_width;
    unsigned exits_count;
    std::vector<std::vector<int>> labyrinth;
    std::vector<std::vector<int>> weight_map;
    std::vector<std::pair<int, int>> exits;
};