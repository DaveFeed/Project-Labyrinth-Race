#pragma once
#include <vector>
#include <iostream>

enum TILE_TYPES {
    EMPTY = 0,
    WALL = 1,
    WALL_INTERSECT = 2,
    EXIT = 3,
    HUMAN = 4,
    BOT = 5,
    FIRE = 6
};

class Labyrinth
{
public:
    Labyrinth(unsigned height = 20, unsigned width = 20, int exits_count = 2);

    void init();
    void draw();
    void draw_wm();
    bool is_wall(int x, int y) const;
    bool is_wall(std::pair<int, int> pos) const;
    bool is_exit(int x, int y) const;
    bool is_exit(std::pair<int, int> pos) const;
    std::vector<std::vector<int>>& get_lab();
    std::vector<std::vector<int>> get_weight_map() const;
    std::vector<std::pair<int, int>> get_exits() const;
    int get_min();
    int get_max();

    // first argument is player, second is bot
    std::vector<std::pair<int, int>> generate_positions(int fire_amount);

    std::pair<int, int> get_labyrinth_size() const;
    
private:
    unsigned vec_height;
    unsigned vec_width;
    unsigned room_height;
    unsigned room_width;
    unsigned exits_count;

    std::vector<std::vector<int>> labyrinth;
    std::vector<std::vector<int>> weight_map;
    std::vector<std::pair<int, int>> exits;


    void addExits();
    void addLoops(int walls);
    std::vector<std::vector<int>> bfs(std::pair<int, int> startPoint);
    void generateWeightMap();
    int max = -1;
};