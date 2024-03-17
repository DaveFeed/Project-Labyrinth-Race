#pragma once
#include <iostream>

#include "Game.h"
#include "Labyrinth.h"
#include "UI.h"
#include "Player.h"

Game::Game() {
	difficulty = Rookie;
	player = Player();
	labyrinth = Labyrinth();
	ui = UI();
}

void Game::start() {
	std::cout << "Successfully started the game!" << std::endl;
}