#pragma once
#include "Player.h"
#include "Labyrinth.h"
#include "UI.h"

class Game
{
public:
	Game();
	enum DIFFICULTY { Rookie, Easy, Medium, Hard };

	void init();
	void loop();
	void play();

	void start();

	int handleMenuInputs(int choices, int currentPosition);
private:
	UI ui;
	Labyrinth labyrinth;
	Player player;
	DIFFICULTY difficulty;

	UI::MENU_STATES menuState; 
	UI::KEYS lastKey;
	bool startGame;
};

