#pragma once
#include "Labyrinth.h"
#include "Player.h"
#include "Fire.h"

class Game
{
public:
	Game();
	~Game();

	void start();
	void loop();

private:
	enum class DIFFICULTY {
		Rookie,
		Easy,
		Medium,
		Hard
	};

	enum class STATE {
		Playing = 0,
		Won = 1,
		Lost = 2,
	};

	DIFFICULTY difficulty;
	STATE game_state;

	Labyrinth labyrinth;
	Player* player = nullptr;
	Player* bot = nullptr;
	Fire fire;

	STATE check_game_state();
};