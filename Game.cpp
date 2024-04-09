#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Game.h"
#include "Human.h"
#include "Helpers.h"
#include "RookieBot.h"
#include "EasyBot.h"
#include "MediumBot.h"
#include "HardBot.h"
#include "UI.h"

Game::Game() 
:labyrinth(10,10,2)
,fire(labyrinth)
{
	srand(time(NULL));
	fire_amnt = (rand() % 3) + 1;
	difficulty = DIFFICULTY::Medium;

	game_state = STATE::Playing;
}

Game::~Game() {
	Helpers::nonblock(1);
	delete player;
	delete bot;
}

void Game::start() {
	Helpers::clear();
	Helpers::nonblock(0);
	// difficulty = static_cast<DIFFICULTY>(start_game());
	// if(difficulty == DIFFICULTY::Exit) {
	// 	return;
	// }
	// Helpers::resizeConsole(80, 60);
	labyrinth.init();
	Helpers::clear();
	labyrinth.draw();
	
	auto positions = labyrinth.generate_positions(fire_amnt);

	player = new Human(positions[0], labyrinth);
	
	switch (difficulty)
	{
	case DIFFICULTY::Rookie:
		bot = new RookieBot(positions[1], labyrinth);
		break;
	case DIFFICULTY::Easy:
		bot = new EasyBot(positions[1], labyrinth);
		break;
	case DIFFICULTY::Medium:
		bot = new MediumBot(positions[1], labyrinth);
		break;
	case DIFFICULTY::Hard:
		// bot = new HardBot(positions[1], labyrinth);
		break;
	default:
		break;
	}

	for(int i = 0; i < fire_amnt; ++i) {
		fire.set_pos(positions[i + 2]);
	}

	player->draw();
	bot->draw();
	fire.draw();

	loop();
}


void Game::loop() {
	while(game_state == STATE::Playing) {
		// Helpers::hideCursor();
		fire.update();
		player->move();
		bot->move();

		game_state = check_game_state();
		if (game_state == STATE::Won) {
			player->draw();
			fflush(stdout);
			//TODO
			return;
		}
		else if(game_state == STATE::Won) {
			bot->draw();
			fflush(stdout);
			// usleep(500000);

			fire.draw();
			fflush(stdout);
			//TODO
			return;
		}

		player->draw();
		fflush(stdout);
		// usleep(500000);
		bot->draw();
		fflush(stdout);
		// usleep(500000);

		fire.draw();
		fflush(stdout);
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