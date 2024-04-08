#include "Player.h"

Player::Player(){}

Player::Player(std::pair<int, int> pos): pos(pos) {}

Player::Player(int x, int y): pos(std::make_pair(x, y)) {}

void Player::set_pos(std::pair<int, int> pos) {
    this->pos = pos;
}

void Player::set_pos(int x, int y) {
    pos = std::make_pair(x, y);
}

void Player::clear_pos() {
    std::cout << "\x1B[" << prev_pos.second + 1 << ";" << prev_pos.first + 1 << "f";
    std::cout << ' ';
    std::cout << "\x1B[" << 50 << ";" << 1 << "f";
}