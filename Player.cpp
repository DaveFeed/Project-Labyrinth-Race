#include "Player.h"
#include "Helpers.h"

Player::Player(){}

Player::Player(std::pair<int, int> pos): pos(pos) {}

Player::Player(int x, int y): pos(std::make_pair(x, y)) {}

void Player::clear_pos() {
    Helpers::draw_char_at(prev_pos, ' ');
}

void Player::draw() {
	Helpers::draw_char_at(pos, sprite);
}

std::pair<int, int> Player::get_pos() {
    return pos;
}

void Player::kill() {
    is_dead = true;
}