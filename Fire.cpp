#include "Fire.h"
#include "Helpers.h"

Fire::Fire() {}
Fire::Fire(int amount): amount(amount) {}

void Fire::update(const Labyrinth& labyrinth) {
    std::vector<std::pair<int, int>> to_add;
    for (auto it : fire_pos) {
        int x = it.first;
        int y = it.second;
        if (!labyrinth.is_wall(x - 1, y)) {
            to_add.emplace_back(x - 2, y);
        }
        if (!labyrinth.is_wall(x + 1, y)) {
            to_add.emplace_back(x + 2, y);
        }
        if (!labyrinth.is_wall(x, y - 1)) {
            to_add.emplace_back(x, y - 2);
        }
        if (!labyrinth.is_wall(x, y + 1)) {
            to_add.emplace_back(x, y + 2);
        }
    }
    for (auto pair : to_add) {
        fire_pos.insert(pair);
    }
}

void Fire::draw() {
	for (auto pair : fire_pos) {
		Helpers::draw_char_at(pair, sprite);
	}
}

void Fire::set_pos(std::pair<int, int> pos, const Labyrinth& labyrinth) {
	fire_pos.insert(pos);
    for (int i = 1; i < amount; ++i) {
        update(labyrinth);
    }
}

std::set<std::pair<int, int>> Fire::get_fire_pos() const {
    return fire_pos;
}