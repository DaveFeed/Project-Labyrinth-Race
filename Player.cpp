#include "Player.h"
#include "Helpers.h"

Player::Player(std::pair<int, int> pos, Labyrinth& labyrinth): pos(pos), labyrinth(labyrinth) {}

Player::Player(int x, int y, Labyrinth& labyrinth): pos(std::make_pair(x, y)), labyrinth(labyrinth) {}

void Player::clear_pos() {
    Helpers::draw_char_at(prev_pos, ' ');
}

std::pair<int, int> Player::get_pos() {
    return pos;
}

void Player::kill() {
    is_dead = true;
}

bool Player::dead() {
    return is_dead;
}