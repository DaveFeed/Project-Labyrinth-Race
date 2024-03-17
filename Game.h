#pragma once
#include "Player.h"
#include "Labyrinth.h"
#include "UI.h"
enum Difficulty { Rookie, Easy, Medium, Hard };

class Game
{
private:
	UI ui;
	Labyrinth labyrinth;
	Player player;
	Difficulty difficulty;

public:
	Game();
	void start();
};

