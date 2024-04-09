#include "UI.h"
#include <unistd.h>
#include <iostream>

static void type_text(std::string str, unsigned int ml_seconds = 100000) {
    for(int i = 0; i < str.length(); ++i) {
    std::cout << str[i];
    fflush(stdout);
    usleep(ml_seconds);
    }
}

static void delete_text(int x, int y, unsigned int ml_seconds = 50000) {
    Helpers::set_cursor_position(x-1, y-1);
    for(int i = 0; i < x; ++i) {
        std::cout << "\b \b";
        fflush(stdout);
        usleep(ml_seconds);
  }
}

int difficulty_check() {
    std::string choose = "Choose diffiulty:\n";
    std::string rookie = "1.Rookie\n";
    std::string easy = "2.Easy\n";
    std::string medium = "3.Medium\n";
    std::string hard = "4.Hard\n";
    type_text(choose);
    usleep(300000);
    type_text(rookie, 60000);
    type_text(easy, 60000);
    type_text(medium, 60000);
    type_text(hard, 60000);
    int choice;
    bool next = false;
    Helpers::set_cursor_position(1, 6);
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

int start_game() {
    std::string hello = "Hello player! ";
    std::string wanna = "Wanna play?\n";
    std::string play = "1.Play\n";
    std::string exit = "2.Exit\n";
    type_text(hello);
    usleep(100000);
    type_text(wanna);
    usleep(300000);
    type_text(play);
    usleep(80000);
    type_text(exit);
    int choice;
    bool next = false;
    Helpers::set_cursor_position(1, 6);
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