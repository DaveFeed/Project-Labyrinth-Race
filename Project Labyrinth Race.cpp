#include "Game.h"

#ifdef WIN32
void terminal_clear() {
	system("cls");
}
#else
void terminal_clear() {
	system("clear");
}
#endif

int main()
{
	terminal_clear();
	Game game;
	game.start();
  	std::cout << "\x1B[" << 49 << ";" << 1 << "f";
	return 0;
}
