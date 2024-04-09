#pragma once
#include <vector>
#include <string>

class Helpers
{
public:
	static void clear();
	static void nonblock(int state);

	static int read_char();

	static void set_cursor_position(int x, int y);
	static void set_cursor_position(std::pair<int, int> p);
	static void drop_cursor();

	static void draw_char_at(int x, int y, char c);
	static void draw_char_at(std::pair<int, int> p, char c);

	static void draw_string_at(int x, int y, std::string s);
	static void draw_string_at(std::pair<int, int> p, std::string s);

	static void resizeConsole(unsigned width, unsigned height);
	static void hideCursor();
};
