#include "Labyrinth.h"
#include <vector>
#include <stack>

Labyrinth::Labyrinth(unsigned height, unsigned width):
height(height)
,width(width)
,data(width, std::vector<int>(height, 0))
{
    srand(time(NULL));
    std::cout << "Successfully initialized labyrinth!\n";
}

void Labyrinth::init()
{
    std::stack<std::pair<int, int>> st;             //for dfs
    std::vector<char> used(height * width, false);

    int x = (rand() % width);                       //where to start dfs
    int y = (rand() % height);

    auto index = [&](int x, int y) {                //lambda function that gets (x, y) coords and returns its index
        return (y * width) + x;
    };

    st.push(std::make_pair(x, y));

    while(!st.empty()) {
        used[index(x, y)] = true;
        //checking available neighbors
        std::vector<int> neighs;

        if(x > 0) {                         //has left neighbor
            if(!used[index(x - 1, y)])      //the left neighbor has not been visited
                neighs.push_back(PATHS::LEFT);
        }
        if(x < width - 1) {                 //has right neighbor
            if(!used[index(x + 1, y)])      //the right neighbor has not been visited
                neighs.push_back(PATHS::RIGHT);
        }
        if(y > 0) {                         //has upper neighbor
            if(!used[index(x, y - 1)])      //the upper neighbor has not been visited
                neighs.push_back(PATHS::UP);
        }
        if(y < height - 1) {                //has bottom neighbor
            if(!used[index(x, y + 1)])      //the bottom neighbor has not been visited
                neighs.push_back(PATHS::DOWN);
        }

        // randomly choosing one neighbor, if no available neighbors then go back
        if(!neighs.empty()) {
            int neighbor_dir = neighs[rand() % neighs.size()];

            switch(neighbor_dir) {
                case PATHS::LEFT:
                    data[x][y] |= PATHS::LEFT;
                    --x;
                    data[x][y] |= PATHS::RIGHT;
                    st.push(std::make_pair(x, y));
                    break;
                case PATHS::RIGHT:
                    data[x][y] |= PATHS::RIGHT;
                    ++x;
                    data[x][y] |= PATHS::LEFT;
                    st.push(std::make_pair(x, y));
                    break;
                case PATHS::UP:
                    data[x][y] |= PATHS::UP;
                    --y;
                    data[x][y] |= PATHS::DOWN;
                    st.push(std::make_pair(x, y));
                    break;
                case PATHS::DOWN:
                    data[x][y] |= PATHS::DOWN;
                    ++y;
                    data[x][y] |= PATHS::UP;
                    st.push(std::make_pair(x, y));
                    break;
            }
        }
        else {
            st.pop();
            if(!st.empty()) {
                x = st.top().first;
                y = st.top().second;
            }
        }
    }
    
    // CREATING LOOPS
    for(int i = 0; i < 100; ++i) {
        while(true) {
            int x = rand() % width;
            int y = rand() % height;

            int available_path = 0b1111;
            if(x == 0)
                available_path -= PATHS::LEFT;
            if(x == width - 1)
                available_path -= PATHS::RIGHT;
            if(y == 0)
                available_path -= PATHS::UP;
            if(y == height - 1)
                available_path -= PATHS::DOWN;
            
            //leave bits that are 1 only in available_path
            available_path |= data[x][y];
            available_path -= data[x][y];
            
            if((available_path & 0b1111) != 0) {
                bool cond = false;
                while(!cond) {
                    int num = rand() % 4;
                    switch(num) {
                        case 0:
                            if((available_path & PATHS::DOWN) != 0) {
                                data[x][y] |= PATHS::DOWN;
                                data[x][y+1] |= PATHS::UP;
                                cond = true;
                            }
                            break;
                        case 1:
                            if((available_path & PATHS::UP) != 0) {
                                data[x][y] |= PATHS::UP;
                                data[x][y-1] |= PATHS::DOWN;
                                cond = true;
                            }
                            break;
                        case 2:
                            if((available_path & PATHS::LEFT) != 0) {
                                data[x][y] |= PATHS::LEFT;
                                data[x-1][y] |= PATHS::RIGHT;
                                cond = true;
                            }
                            break;
                        case 3:
                            if((available_path & PATHS::RIGHT) != 0) {
                                data[x][y] |= PATHS::RIGHT;
                                data[x+1][y] |= PATHS::LEFT;
                                cond = true;
                            }
                            break;
                    }
                }
                break;
            }
        }
    }
}
