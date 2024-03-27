#pragma once
#include <iostream>
#include <vector>
class UI
{
public:
	UI();

	enum class MENU_STATES {
		DEFAULT = 0,
		SETTINGS = 1,
		DIFFICULTY = 2,
	};

	enum KEYS {
		UP_ARROW = 72,
		DOWN_ARROW = 80,
		LEFT_ARROW = 75,
		RIGHT_ARROW = 77,
		W = 119,
		A = 97,
		S = 115,
		D = 100,
		ENTER = 13,
		SPACE = 32
	};

	enum COLORS {
		BLACK = 0,
		RED = 1,
		GREEN = 2,
		YELLOW = 3,
		BLUE = 4,
		MAGENTA = 5,
		CYAN = 6,
		WHITE = 7,
		BRIGHT_BLACK = 8,
		BRIGHT_RED = 9,
		BRIGHT_GREEN = 10,
		BRIGHT_YELLOW = 11,
		BRIGHT_BLUE = 12,
		BRIGHT_MAGENTA = 13,
		BRIGHT_CYAN = 14,
		BRIGHT_WHITE = 15
	};

	void init();
	void clear();
	void setCursorPosition(unsigned x, unsigned y);
	void setColor(COLORS foreground);
	void setColor(COLORS foreground, COLORS background);
	void printChar(const wchar_t character);
	void printString(const wchar_t* string);
	void printString(const std::wstring* string);
	void resizeConsole(unsigned width, unsigned heigth);
	void drawCursor(int currentPosition);
	void clearCursor(int currentPosition);
	void hideCursor();
	void labyrinth(const std::vector<std::vector<char>>* labyrinth);

	KEYS awaitKeypress();
	
	int menu(MENU_STATES state);

private:
	unsigned windowWidth;
	unsigned windowHeight;
	unsigned heightOffset;
	COLORS defaultForeground;
	COLORS defaultBackground;

	COLORS cursorForeground;
	unsigned cursorOffset;
	wchar_t cursor = L'►';

};