#include "Human.h"
#include <iostream>
#include <cstdlib>

#ifdef WIN32
#include <conio.h>
//todo
#else
#include <termios.h>
#include <unistd.h>

//this function makes getc() work without expecting enter
void nonblock(int state)
{
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state==0)
    {
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==1)
    {
        ttystate.c_lflag |= ICANON;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}
int read_char() {
    return getch
}
#endif

Human::Human() {     //to avoid code duplication created default constructor, 
    nonblock(0);        //but error occured(delegation with mem-initialization)
}

Human::~Human() {
    nonblock(1);
}

Human::Human(std::pair<int, int> pos): Player(pos) {
    nonblock(0);
}

Human::Human(int x, int y):Player(std::make_pair(x, y)) {
    nonblock(0);
}

std::pair<int, int> Player::get_pos() {
    return pos;
}

bool Human::move(const Labyrinth& labyrinth) {
    prev_pos = pos;
    bool moved = false;
    while(!moved) {
        key_pressed = getchar();
        std::cout << "\r \r";
        switch(key_pressed) {
            case KEYS::w:
                if(!labyrinth.is_wall(pos.first, pos.second - 1)) {
                    pos.second -= 2;
                    moved = true;
                }
                break;

            case KEYS::a:
                if(!labyrinth.is_wall(pos.first - 1, pos.second)) {
                    pos.first -= 2;
                    moved = true;
                }
                break;

            case KEYS::s:
                if(!labyrinth.is_wall(pos.first, pos.second + 1)) {
                    pos.second += 2;
                    moved = true;
                }
                break;

            case KEYS::d:
                if(!labyrinth.is_wall(pos.first + 1, pos.second)) {
                    pos.first += 2;
                    moved = true;
                }
                break;
            case KEYS::q:
                return false;
            default:
                break;
        }
    }
    return true;
}

void Human::draw() {
    std::cout << "\x1B[" << pos.second + 1 << ";" << pos.first + 1 << "f";
    std::cout << '$';
    std::cout << "\x1B[" << 50 << ";" << 1 << "f";
}