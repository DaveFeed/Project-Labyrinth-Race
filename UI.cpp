#include <fcntl.h>
#include <vector>

#ifdef _WIN32
#include <io.h>
#include <stdio.h>
#include <conio.h>
#endif

#include "UI.h"
#include "Labyrinth.h"

UI::UI()
{
	windowWidth = 100;
	windowHeight = 50;

	heightOffset = 2;
	cursorOffset = 6;

	defaultForeground = COLORS::BRIGHT_WHITE;
	defaultBackground = COLORS::BLACK;

	cursorForeground = COLORS::BRIGHT_YELLOW;
}

void UI::init()
{
#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif

	resizeConsole(windowWidth, windowHeight);
	setColor(defaultForeground, defaultBackground);
	clear();
}

void UI::clear()
{
	system("cls");
};

void UI::setColor(COLORS foreground)
{
	wprintf(L"\033[38;5;%dm", foreground);
}

void UI::setColor(COLORS foreground, COLORS background)
{
	wprintf(L"\033[38;5;%dm", foreground);
	wprintf(L"\033[48;5;%dm", background);
}

void UI::setCursorPosition(unsigned x, unsigned y)
{
	wprintf(L"%c[%d;%df", 0x1B, y, x);
};

void UI::clearCursor(int height)
{
	setCursorPosition(windowWidth / 2 - cursorOffset, windowHeight / 2 - heightOffset + 2 + height);
	printChar(' ');
	hideCursor();
};

void UI::resizeConsole(unsigned width, unsigned height)
{
	wprintf(L"\033[8;%d;%dt", height, width);
};

void UI::printChar(const wchar_t character)
{
	wprintf(L"%lc", character);
};

void UI::printString(const wchar_t *string)
{
	wprintf(L"%ls", string);
};

void UI::printString(const std::wstring *string)
{
	wprintf(L"%ls", string->c_str());
};

void UI::drawCursor(int currentPosition)
{
	// +2 for all menu options having headers of 2 lines, fix this via having another cursorHeightOffset
	setCursorPosition(windowWidth / 2 - cursorOffset, windowHeight / 2 - heightOffset + 2 + currentPosition);
	setColor(cursorForeground);
	printChar(cursor);
	setColor(defaultForeground);
	hideCursor();
};

void UI::hideCursor()
{
	setCursorPosition(0, windowHeight);
	std::wcout << L"\033[?25l";
};

int UI::menu(MENU_STATES state)
{
	switch (state)
	{
	case UI::MENU_STATES::DEFAULT:
	{
		const int options = 3;
		std::vector<std::wstring> texts{
			L"Menu",
			L"────────────",
			L"Play",
			L"Settings",
			L"Exit",
		};
		for (size_t i = 0; i < texts.size(); ++i)
		{
			setCursorPosition((windowWidth - texts[i].length()) / 2, windowHeight / 2 - heightOffset + i);
			printString(&texts[i]);
		}

		hideCursor();
		return options;
	}
	case UI::MENU_STATES::SETTINGS:
	{
		const int options = 2;
		std::vector<std::wstring> texts{
			L"Settings",
			L"────────────",
			L"Difficulty",
			L"Back",
		};
		for (size_t i = 0; i < texts.size(); ++i)
		{
			setCursorPosition((windowWidth - texts[i].length()) / 2, windowHeight / 2 - heightOffset + i);
			printString(&texts[i]);
		}

		hideCursor();
		return options;
	}
	case UI::MENU_STATES::DIFFICULTY:
	{
		const int options = 4;
		const std::vector<std::wstring> texts{
			L"Difficulty",
			L"────────────",
			L"Rookie",
			L"Easy",
			L"Medium",
			L"Hard",
		};
		for (size_t i = 0; i < texts.size(); ++i)
		{
			setCursorPosition((windowWidth - texts[i].length()) / 2, windowHeight / 2 - heightOffset + i);
			printString(&texts[i]);
		}

		hideCursor();
		return options;
	}
	default:
		return 0;
	}
};

UI::KEYS UI::awaitKeypress()
{
	wchar_t c = 0;
	do
	{
		c = 0;

		switch ((c = _getch()))
		{
		case KEYS::UP_ARROW:
		case KEYS::DOWN_ARROW:
		case KEYS::RIGHT_ARROW:
		case KEYS::LEFT_ARROW:
		case KEYS::W:
		case KEYS::A:
		case KEYS::S:
		case KEYS::D:
		case KEYS::ENTER:
		case KEYS::SPACE:
			break;
		default:
			c = 0;
			break;
		}

	} while (!c);

	return static_cast<KEYS>(c);
};

// todo:: (refactor) ill do this when im better at coding
// did this to avoid static_cast's as enums have the same names and class enums would require casting
namespace InnerWalls
{
	enum
	{
		TOP_LEFT = L'┌',
		TOP_RIGHT = L'┐',
		BOTTOM_LEFT = L'└',
		BOTTOM_RIGHT = L'┘',
		HORIZONTAL = L'─',
		HORIZONTAL_UP = L'┴',
		HORIZONTAL_DOWN = L'┬',
		VERTICAL = L'│',
		VERTICAL_LEFT = L'├',
		VERTICAL_RIGHT = L'┤',
		CROSS = L'┼',
		NONE = L'▪'
	};
}

namespace OutterWalls
{
	enum
	{
		TOP_LEFT = L'╔',
		TOP_RIGHT = L'╗',
		BOTTOM_LEFT = L'╚',
		BOTTOM_RIGHT = L'╝',
		HORIZONTAL = L'═',
		HORIZONTAL_UP = L'╧',
		HORIZONTAL_DOWN = L'╤',
		VERTICAL = L'║',
		VERTICAL_LEFT = L'╟',
		VERTICAL_RIGHT = L'╢',
	};
}

void UI::labyrinth(std::vector<std::vector<int>> *labyrinth)
{
	// todo:: (add) no checks if labyrinth is square
	for (size_t i = 0; i < labyrinth->size(); ++i)
	{
		setCursorPosition((windowWidth - labyrinth->size()) / 2, (windowHeight - labyrinth->size()) / 2 + i);

		for (size_t j = 0; j < labyrinth->size(); ++j)
		{
			switch ((*labyrinth)[i][j])
			{
			case Labyrinth::TILE_TYPES::EMPTY:
				printChar(L' ');
				break;
			case Labyrinth::TILE_TYPES::WALL:
			{
				if (i == 0)
				{
					if (j == 0)
					{
						printChar(OutterWalls::TOP_LEFT);
					}
					else if (j == labyrinth->size() - 1)
					{
						printChar(OutterWalls::TOP_RIGHT);
					}
					else if ((*labyrinth)[i + 1][j] == Labyrinth::TILE_TYPES::WALL)
					{
						printChar(OutterWalls::HORIZONTAL_DOWN);
					}
					else
					{
						printChar(OutterWalls::HORIZONTAL);
					}
				}
				else if (i == labyrinth->size() - 1)
				{
					if (j == 0)
					{
						printChar(OutterWalls::BOTTOM_LEFT);
					}
					else if (j == labyrinth->size() - 1)
					{
						printChar(OutterWalls::BOTTOM_RIGHT);
					}
					else if ((*labyrinth)[i - 1][j] == Labyrinth::TILE_TYPES::WALL)
					{
						printChar(OutterWalls::HORIZONTAL_UP);
					}
					else
					{
						printChar(OutterWalls::HORIZONTAL);
					}
				}
				else if (j == 0)
				{
					if ((*labyrinth)[i][j + 1] == Labyrinth::TILE_TYPES::WALL)
					{
						printChar(OutterWalls::VERTICAL_LEFT);
					}
					else
					{
						printChar(OutterWalls::VERTICAL);
					}
				}
				else if (j == labyrinth->size() - 1)
				{
					if ((*labyrinth)[i][j - 1] == Labyrinth::TILE_TYPES::WALL)
					{
						printChar(OutterWalls::VERTICAL_RIGHT);
					}
					else
					{
						printChar(OutterWalls::VERTICAL);
					}
				}
				else
				{
					bool hasLeft = (*labyrinth)[i][j - 1] == Labyrinth::TILE_TYPES::WALL;
					bool hasRight = (*labyrinth)[i][j + 1] == Labyrinth::TILE_TYPES::WALL;
					bool hasTop = (*labyrinth)[i - 1][j] == Labyrinth::TILE_TYPES::WALL;
					bool hasBottom = (*labyrinth)[i + 1][j] == Labyrinth::TILE_TYPES::WALL;

					// todo:: (refactor) its 03:55
					if (hasLeft && hasRight && hasTop && hasBottom)
					{
						printChar(InnerWalls::CROSS);
					}
					else if (hasLeft && hasRight && hasTop)
					{
						printChar(InnerWalls::HORIZONTAL_UP);
					}
					else if (hasLeft && hasRight && hasBottom)
					{
						printChar(InnerWalls::HORIZONTAL_DOWN);
					}
					else if (hasLeft && hasBottom && hasTop)
					{
						printChar(InnerWalls::VERTICAL_RIGHT);
					}
					else if (hasRight && hasBottom && hasTop)
					{
						printChar(InnerWalls::VERTICAL_LEFT);
					}
					else if (hasLeft && hasBottom)
					{
						printChar(InnerWalls::TOP_RIGHT);
					}
					else if (hasRight && hasBottom)
					{
						printChar(InnerWalls::TOP_LEFT);
					}
					else if (hasLeft && hasTop)
					{
						printChar(InnerWalls::BOTTOM_RIGHT);
					}
					else if (hasRight && hasTop)
					{
						printChar(InnerWalls::BOTTOM_LEFT);
					}
					else if (hasLeft && hasBottom)
					{
						printChar(InnerWalls::TOP_RIGHT);
					}
					else if (hasLeft && hasBottom)
					{
						printChar(InnerWalls::TOP_RIGHT);
					}
					else if (hasLeft || hasRight)
					{
						printChar(InnerWalls::HORIZONTAL);
					}
					else if (hasBottom || hasTop)
					{
						printChar(InnerWalls::VERTICAL);
					}
					else
					{
						printChar(InnerWalls::NONE);
					}
				}
				break;
			}
			case Labyrinth::TILE_TYPES::PLAYER:
				// todo:: (change) placeholders
				printChar(L'P');
				break;
			case Labyrinth::TILE_TYPES::BOT:
				// todo:: (change) placeholders
				printChar(L'B');
				break;
			case Labyrinth::TILE_TYPES::FIRE:
				// todo:: (change) placeholders
				printChar(L'F');
				break;
				case Labyrinth::TILE_TYPES::EXIT:
				// todo:: (change) placeholders
				setColor(COLORS::BRIGHT_GREEN);
				printChar(L'⃝');
				setColor(defaultForeground);
				break;
			}
		}
	}
};
