#pragma once

#include "Helpers.h"

#ifdef _WIN32 
static 
#endif 
class UI {
public:
    static void sleep_ml(unsigned int mls);
    static int start_game();
    static int difficulty_check();
    static void you_win();
    static void you_lose();
    static void delete_text(int x, int y, unsigned int ml_seconds = 50000);
};