#include "UI.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
void UI::sleep_ml(unsigned int mls) {
    Sleep(mls);
}
#else
#include <unistd.h>
void UI::sleep_ml(unsigned int mls) {
    usleep(mls);
}
#endif


static void type_text(std::string str, unsigned int ml_seconds = 100000) {
    for(int i = 0; i < str.length(); ++i) {
    std::cout << str[i];
    fflush(stdout);
    UI::sleep_ml(ml_seconds);
    }
}

void UI::delete_text(int x, int y, unsigned int ml_seconds) {
    Helpers::set_cursor_position(x-1, y-1);
    for(int i = 0; i < x; ++i) {
        std::cout << "\b \b";
        fflush(stdout);
        UI::sleep_ml(ml_seconds);
  }
}

int UI::difficulty_check() {
    std::string choose = "Choose diffiulty:\n";
    std::string rookie = "1.Rookie\n";
    std::string easy = "2.Easy\n";
    std::string medium = "3.Medium\n";
    std::string hard = "4.Hard\n";
    type_text(choose);
    sleep_ml(300000);
    type_text(rookie, 60000);
    type_text(easy, 60000);
    type_text(medium, 60000);
    type_text(hard, 60000);
    int choice;
    bool next = false;
    Helpers::set_cursor_position(0, 20);
    while(!next) {
        choice = Helpers::read_char();
        std::cout << "\b \b";
        choice -= ('1' - 1);
        switch(choice) {
            case 1:
            case 2:
            case 3:
            case 4:
                next = true;
            break;
            default:
            break;
        }
    }
    delete_text(hard.length(), 5);
    delete_text(medium.length(), 4);
    delete_text(easy.length(), 3);
    delete_text(rookie.length(), 2);
    delete_text(choose.length(), 1, 30000);
    return choice;
}

int UI::start_game() {
    std::string hello = "Hello player! ";
    std::string wanna = "Wanna play?\n";
    std::string play = "1.Play\n";
    std::string exit = "2.Exit\n";
    type_text(hello);
    sleep_ml(800000);
    type_text(wanna);
    sleep_ml(800000);
    type_text(play);
    sleep_ml(500000);
    type_text(exit);
    int choice;
    bool next = false;
    Helpers::set_cursor_position(0, 20);
    while(!next) {
        choice = Helpers::read_char();
        std::cout << "\b \b";
        choice -= ('1' - 1);
        switch(choice) {
            case 1:
            case 2:
                next = true;
            break;
            default:
            break;
        }
    }
    delete_text(exit.length(), 3);
    delete_text(play.length(), 2);
    delete_text(wanna.length() + hello.length(), 1, 30000);
    if(choice == 1) {
        return difficulty_check();
    }
    else {
        return 0;
    }
}

void UI::you_win() {
    std::string congr = "Congratulations!\n";
    std::string win =  "You win!\n";
    std::string press =  "Press any key to exit\n";

    type_text(congr);
    sleep_ml(1000000);
    type_text(win);
    sleep_ml(1000000);
    type_text(press, 80000);
}

void UI::you_lose() {
    std::string lost = "You lose\n";
    std::string luck =  "Better luck next time!\n";
    std::string press =  "Press any key to exit\n";

    type_text(lost);
    sleep_ml(1000000);
    type_text(luck, 80000);
    sleep_ml(1000000);
    type_text(press, 80000);
}