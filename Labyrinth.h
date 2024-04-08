#pragma once
#include <vector>

class Labyrinth
{
public:
    Labyrinth (unsigned height = 20, unsigned width = 20);

    void init();
    void draw();

private:
    unsigned rooms_height;
    unsigned rooms_width;
    unsigned vec_height;
    unsigned vec_width;
    unsigned exits_count;

    enum TILE_TYPES {
        EMPTY = 0,
        WALL = 1,
        WALL_INTERSECT = 2,
        EXIT = 3
    };

    std::vector<std::vector<int>> labyrinth;
    std::vector<std::vector<int>> weight_map;
    std::vector<std::pair<int, int>> exits;

    void addExits();
    void addLoops(int walls);
    std::vector<std::vector<int>> bfs(std::pair<int, int> startPoint);
    void generateWeightMap();
};