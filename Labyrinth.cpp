#include "Labyrinth.h"
#include <vector>
#include <stack>

Labyrinth::Labyrinth(unsigned height, unsigned width):
height(height)
,width(width)
,labyrinth(width * 2 + 1, std::vector<int>(height * 2 + 1, 1))
{
    srand(time(NULL));
    std::cout << "Successfully initialized labyrinth!\n";
}

void Labyrinth::init()
{
    std::stack<std::pair<int, int>> st;

    int x = (rand() % 2 * width);
    if(x % 2 == 0) {
        ++x;
    }                  
    int y = (rand() % 2 * height);
    if(y % 2 == 0) {
        ++y;
    }

    st.push(std::make_pair(x, y));

    while(!st.empty()) {
        labyrinth[x][y] = 0;
        std::vector<std::pair<int, int>> neighs;

        if(x > 1) {                         
            if(labyrinth[x - 2][y] == 1)      
                neighs.push_back(std::make_pair(x - 2, y));
        }
        if(x < 2 * width - 1) {                
            if(labyrinth[x + 2][y] == 1)      
                neighs.push_back(std::make_pair(x + 2, y));
        }
        if(y > 1) {                         
            if(labyrinth[x][y - 2] == 1)      
                neighs.push_back(std::make_pair(x, y - 2));
        }
        if(y < 2 * height - 1) {                
            if(labyrinth[x][y + 2] == 1)      
                neighs.push_back(std::make_pair(x, y + 2));
        }

        if(!neighs.empty()) {
            int neighbor = rand() % neighs.size();
            int new_x = neighs[neighbor].first;
            int new_y = neighs[neighbor].second;
            labyrinth[(x + new_x) / 2][(y + new_y) / 2] = 0;
            x = new_x;
            y = new_y;
            st.push(std::make_pair(x, y));
        }
        else {
            st.pop();
            if(!st.empty()) {
                x = st.top().first;
                y = st.top().second;
            }
        }
    }

    for(int i = 2; i < width * 2; i += 2) {
        for(int j = 2; j < height * 2; j += 2) {
            labyrinth[i][j] = 2;                        //on odd x odd places are wall intersections(number 2)
        }
    }
    
    std::cout << "Labyrinth created, now adding loops\n";

    // CREATING LOOPS
    for(int i = 0; i < 100; ++i) {
        while(true) {
            int x = rand() % (2 * width - 1) + 1;
            int y = rand() % (2 * height -1) + 1;
            std::cout << "x = " << x << " y = " << y << std::endl;
            if(x % 2 == 0) {
                while(y % 2 == 0) {
                    y = y + 1;
                }
            } else {
                if(y % 2 != 0) {
                    y = (y + 1) % (2 * width - 1);
                }
            }
            std::cout << "new x = " << x << " new y = " << y << std::endl;


            if(labyrinth[x][y] == 1) {
                labyrinth[x][y] = 0;
                break;
            }
        }
        std::cout << "wall created\n";
    }
    std::cout << "Loops added\n";
}

void Labyrinth::draw()
{
    int wall = 0;

    //i shows the rows
    for(int i = 0; i < 2 * height + 1; ++i) {
        //j shows the columns
        for(int j = 0; j < 2 * width + 1; ++j) {
            if(labyrinth[i][j] == 0) {
                std::cout << ' ';
            }
            else if(labyrinth[i][j] == 2) {
                std::cout << '+';
            }
            else {
                if(j == 0 || j == 2 * width || i % 2 != 0) {
                    std::cout << '|';
                    ++wall;
                }
                else {
                    std::cout << '-';
                    ++wall;
                }
            }
        }

        std::cout << std::endl;
    }

    std::cout << wall << std::endl;
}
