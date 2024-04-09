#pragma once
#include "Helpers.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

void Helpers::clear() {
	system(
    #ifdef _WIN32
        "cls"
    #else
        "clear"
    #endif
    );
}

#ifdef _WIN32
#include <conio.h>
void Helpers::nonblock(int a) {}
int Helpers::read_char() {
    return _getch();
}
#else
#include <termios.h>
#include <unistd.h>

//this function makes getc() work without expecting enter
void Helpers::nonblock(int state)
{
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == 0)
    {
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state == 1)
    {
        ttystate.c_lflag |= ICANON;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}
int Helpers::read_char() {
    return getchar();
}
#endif

void Helpers::set_cursor_position(int x, int y) {
	std::cout << "\x1B[" << y + 1 << ";" << x + 1 << "f";
}

void Helpers::set_cursor_position(std::pair<int, int> p) {
    std::cout << "\x1B[" << p.second + 1 << ";" << p.first + 1 << "f";
}

void Helpers::draw_char_at(int x, int y, char c) {
    set_cursor_position(x, y);
    std::cout << c;
}

void Helpers::draw_char_at(std::pair<int, int> p, char c) {
    set_cursor_position(p);
    std::cout << c;
}

void Helpers::draw_string_at(int x, int y, std::string s) {
    set_cursor_position(x, y);
    std::cout << s;
}

void Helpers::draw_string_at(std::pair<int, int> p, std::string s) {
    set_cursor_position(p);
    std::cout << s;
}

void Helpers::resizeConsole(unsigned width, unsigned height) {
    std::cout << "\033[8;"<< height << ";"<< width << "t";
};

void Helpers::hideCursor() {
    set_cursor_position(0, 0);
    std::cout << "\033[?25l";
};