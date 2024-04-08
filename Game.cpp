#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Labyrinth.h"
#include "UI.h"
#include "Player.h"

Game::Game() 
:player()
,labyrinth(20, 20)
,ui()
{
	srand(time(NULL));

	difficulty = DIFFICULTY::Rookie;
}

void Game::start() {
	labyrinth.init();
	labyrinth.draw();
	std::cout << "Successfully started the game!" << std::endl;
}