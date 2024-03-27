#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#include "Game.h"
#include "Labyrinth.h"
#include "UI.h"
#include "Player.h"

Game::Game()
	:player()
	, labyrinth(20, 20)
	, ui()
{

	// todo:: (maybe) Move these to Game::init() ?
	difficulty = DIFFICULTY::Rookie;
	menuState = UI::MENU_STATES::DEFAULT;
	startGame = false;
}

void Game::init() {
	ui.init();
	labyrinth.init();
}

void Game::play() {
	// todo:: implement
}

void Game::loop() {
	bool gameOver = false;
	do {
		lastKey = ui.awaitKeypress();
		// update();

		// ui.update(prev locations, new locations);
		gameOver = true;
	} while (!gameOver);
}

void Game::start() {
	init();

	int choices = 0;
	int currentPosition = 0;
	do {
		choices = ui.menu(menuState);
		ui.drawCursor(currentPosition);
		lastKey = ui.awaitKeypress();

		currentPosition = handleMenuInputs(choices, currentPosition);
	} while (!startGame);

	// create Player and Bots according to difficulty
	// spawn fire according to difficulty
	ui.clear();
	// todo:: (i cant be bothered rn) i want to sleep 04:21
	// ui.labyrinth(labyrinth.data);
	loop();
}

int Game::handleMenuInputs(int choices, int currentPosition) {
	// todo:: (maybe) add left and right choices to go into or go out of menu option
	switch (lastKey)
	{
	case UI::KEYS::UP_ARROW:
	case UI::KEYS::W:
		if (currentPosition > 0) {
			ui.clearCursor(currentPosition);
			return --currentPosition;
		}
		return currentPosition;
	case UI::KEYS::DOWN_ARROW:
	case UI::KEYS::S:
		if (currentPosition + 1 < choices) {
			ui.clearCursor(currentPosition);
			return ++currentPosition;
		}
		return currentPosition;
	case UI::KEYS::ENTER:
	case UI::KEYS::SPACE:
		switch (menuState)
		{
		case UI::MENU_STATES::DEFAULT:
			switch (currentPosition)
			{
			case 0: // START
				startGame = true;
				return 0;
			case 1: // SETTINGS
				menuState = UI::MENU_STATES::SETTINGS;
				ui.clear();
				return 0;
			case 2: // EXIT
				ui.setCursorPosition(0, 0);
				exit(0);
				return 0;
			}
			break;
		case UI::MENU_STATES::SETTINGS:
			switch (currentPosition)
			{
			case 0: // DIFFICULTY
				menuState = UI::MENU_STATES::DIFFICULTY;
				ui.clear();
				return 0;
			case 1: // SETTINGS
				menuState = UI::MENU_STATES::DEFAULT;
				ui.clear();
				return 0;
			}
			break;
		case UI::MENU_STATES::DIFFICULTY:
			switch (currentPosition)
			{
			case DIFFICULTY::Rookie:
			case DIFFICULTY::Easy:
			case DIFFICULTY::Medium:
			case DIFFICULTY::Hard:
				difficulty = static_cast<DIFFICULTY>(currentPosition);
				menuState = UI::MENU_STATES::SETTINGS;
				ui.clear();
				return 0;
			}
			break;
		}
		break;
	}
}
