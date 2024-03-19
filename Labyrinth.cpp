#include "Labyrinth.h"

Labyrinth::Labyrinth(unsigned height, unsigned width):
height(height)
,width(width)
,labyrinth(width, std::vector<int>(height, 0))
{
    srand(time(NULL));
    std::cout << "Successfully initialized labyrinth!\n";
}

void Labyrinth::init()
{
    std::stack<std::pair<int, int>> st;                                  //for dfs
    std::vector<char> used(height * width, false);

    int x = (rand() % width);                       //where to start dfs
    int y = (rand() % height);

    auto index = [&](int x, int y) {                //lambda function that gets (x, y) coords and returns its index
        return (y * width) + x;
    };

    st.push(std::make_pair(x, y));
    // std::cout << index(x, y);

    while(!st.empty()) {
        used[index(x, y)] = true;
        //checking available neighbors
        std::vector<int> neighs;

        if(x > 0) {                         //has left neighbor
            if(!used[index(x - 1, y)])      //the left neighbor has not been visited
                neighs.push_back(LEFT_PATH);
        }
        if(x < width - 1) {                 //has right neighbor
            if(!used[index(x + 1, y)])      //the right neighbor has not been visited
                neighs.push_back(RIGHT_PATH);
        }
        if(y > 0) {                         //has upper neighbor
            if(!used[index(x, y - 1)])      //the upper neighbor has not been visited
                neighs.push_back(UP_PATH);
        }
        if(y < height - 1) {                //has bottom neighbor
            if(!used[index(x, y + 1)])      //the bottom neighbor has not been visited
                neighs.push_back(BOTTOM_PATH);
        }

        // randomly choosing one neighbor, if no available neighbors then go back
        if(!neighs.empty()) {
            int neighbor_dir = neighs[rand() % neighs.size()];

            switch(neighbor_dir) {
                case LEFT_PATH:                       //is left neighbor
                    labyrinth[x][y] |= LEFT_PATH;
                    --x;
                    labyrinth[x][y] |= RIGHT_PATH;
                    st.push(std::make_pair(x, y));
                    break;
                case RIGHT_PATH:                      //is right neighbor
                    labyrinth[x][y] |= RIGHT_PATH;
                    ++x;
                    labyrinth[x][y] |= LEFT_PATH;
                    st.push(std::make_pair(x, y));
                    break;
                case UP_PATH:                         //is up neighbor
                    labyrinth[x][y] |= UP_PATH;
                    --y;
                    labyrinth[x][y] |= BOTTOM_PATH;
                    st.push(std::make_pair(x, y));
                    break;
                case BOTTOM_PATH:                     //is bottom neighbor
                    labyrinth[x][y] |= BOTTOM_PATH;
                    ++y;
                    labyrinth[x][y] |= UP_PATH;
                    st.push(std::make_pair(x, y));
                    break;
            }
            // std::cout << "->" << index(x, y);
        }
        else {
            st.pop();
            if(!st.empty()) {
                x = st.top().first;
                y = st.top().second;
                // std::cout << "->" << index(x, y);
            }
        }
    }
    // std::cout << std::endl;
}

void Labyrinth::draw()
{
    std::cout << ' ';
    for(int i = 1; i < 2 * width; ++i)
        std::cout << '_';
    std::cout << std::endl;

    for(int i = 0; i < 2 * height - 1; ++i) {
        std::cout << '|';
        for(int j = 0; j < 2 * width - 1; ++j) {
            if(j % 2 != 0) {
                if(i % 2 != 0)
                    std::cout << '+';
                else {
                    if((labyrinth[j / 2][i / 2] & RIGHT_PATH) == 0)
                        std::cout << '|';
                    else
                        std::cout << ' ';
                }
            }
            else {
                if(i % 2 == 0)
                    std::cout << ' ';
                else {
                    if((labyrinth[j / 2][i / 2] & BOTTOM_PATH) == 0)
                        std::cout << '-';
                    else
                        std::cout << ' ';
                }
            }
        }
        std::cout << '|' << std::endl;
    }

    std::cout << ' ';
    for(int i = 1; i < 2 * width; ++i)
        std::cout << '-';
    std::cout << std::endl;
}
