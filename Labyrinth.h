#pragma once
#include <vector>
#include <iostream>

class Labyrinth
{
public:
    Labyrinth (unsigned height = 20, unsigned width = 20, int exits_count = 2);

    void init();
    void draw();
    void draw_wm();
    bool is_wall(int x, int y) const;
    bool is_wall(std::pair<int, int> pos) const;
    std::vector<std::vector<int>> get_weight_map() const;
    int get_min();
    int get_max();

private:
    unsigned rooms_height;
    unsigned rooms_width;
    unsigned vec_height;
    unsigned vec_width;
    unsigned exits_count;

    std::vector<std::vector<int>> labyrinth;
    std::vector<std::vector<int>> weight_map;
    std::vector<std::pair<int, int>> exits;

    enum TILE_TYPES {
        EMPTY = 0,
        WALL = 1,
        WALL_INTERSECT = 2,
        EXIT = 3
    };

    void addExits();
    void addLoops(int walls);
    std::vector<std::vector<int>> bfs(std::pair<int, int> startPoint);
    void generateWeightMap();
    int max = -1;
};