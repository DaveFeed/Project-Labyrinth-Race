#pragma once
#include "Player.h"
#include "Labyrinth.h"
#include "UI.h"
#include "Human.h"
#include "RookieBot.h"
#include "Fire.h"

class Game
{
public:
	Game();
	void start();
	void game_loop();

private:
	enum class DIFFICULTY { Rookie, Easy, Medium, Hard };
	
	UI ui;
	Labyrinth labyrinth;
	Human player;
	RookieBot bot;
	Fire fire;
	DIFFICULTY difficulty;

	std::pair<int, int> find_position(int distance);
};