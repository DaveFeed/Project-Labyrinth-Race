#pragma once
#include "Player.h"
#include "Labyrinth.h"
#include "UI.h"

class Game
{
public:
	Game();
	void start();

private:
	enum class DIFFICULTY { Rookie, Easy, Medium, Hard };
	UI ui;
	Labyrinth labyrinth;
	Player player;
	DIFFICULTY difficulty;
};

