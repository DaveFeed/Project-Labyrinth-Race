#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Human.h"
#include "Helpers.h"
#include "RookieBot.h"
#include "EasyBot.h"
#include "MediumBot.h"
#include "HardBot.h"

Game::Game() 
:labyrinth(20,20,2),
fire(2)
{
	srand(time(NULL));

	difficulty = DIFFICULTY::Rookie;
	game_state = STATE::Playing;
}

void Game::start() {
	Helpers::resizeConsole(80, 60);
	labyrinth.init();
	
	auto positions = labyrinth.generate_positions();

	player = new Human(positions[0]);
	
	// todo:: (add) dynamic difficulty change, at least command args option
	switch (difficulty)
	{
	case Game::DIFFICULTY::Rookie:
		bot = new RookieBot(positions[1]);
		break;
	case Game::DIFFICULTY::Easy:
		bot = new EasyBot(positions[1]);
		break;
	case Game::DIFFICULTY::Medium:
		// bot = new MediumBot(positions[1]);
		break;
	case Game::DIFFICULTY::Hard:
		// bot = new HardBot(positions[1]);
		break;
	default:
		break;
	}

	fire.set_pos(positions[2], labyrinth);

	labyrinth.draw();

	bot->draw();
	player->draw();
	fire.draw();

	loop();
}


void Game::loop() {
	while(game_state == STATE::Playing) {
		Helpers::hideCursor();
		player->move(labyrinth);
		bot->move(labyrinth);

		fire.update(labyrinth);

		player->clear_pos();
		player->draw();
		
		game_state = check_game_state();
		if (game_state == STATE::Won) {
			// draw only the player and then show that he won
			return;
		}

		bot->clear_pos();
		bot->draw();

		fire.draw();
	}
}

Game::STATE Game::check_game_state() {
	const std::pair<int, int> player_location = player->get_pos();
	const std::pair<int, int> bot_location = bot->get_pos();

	for (const auto& exit : labyrinth.get_exits())
	{
		if (player_location == exit) {
			return STATE::Won;
		}

		if (bot_location == exit) {
			return STATE::Lost;
		}
	}

	for (const auto& f : fire.get_fire_pos())
	{
		if (player_location == f) {
			return STATE::Lost;
		}

		if (bot_location == f) {
			bot->kill();
		}
	}

	return STATE::Playing;
}

Game::~Game() {
	delete player;
	delete bot;
}