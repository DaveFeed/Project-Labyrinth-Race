#include "Labyrinth.h"

Labyrinth::Labyrinth(unsigned height, unsigned width):
rooms_height(height)
,rooms_width(width)
,vec_height(rooms_height * 2 + 1)
,vec_width(rooms_width * 2 + 1)
,labyrinth(vec_width, std::vector<int>(vec_height, 1))
,weight_map(rooms_width, std::vector<int>(rooms_height, 1e6))
,exits_count(2)
,exits()
{
    srand(time(NULL));
}

void Labyrinth::init()
{
    std::stack<std::pair<int, int>> st;
    int walls = (vec_height - 2) * (vec_width - 2) - (rooms_height - 1) * (rooms_width - 1) - 1;
    int rooms = 1;

    int x = (rand() % 2 * rooms_width);
    if(x % 2 == 0) {
        ++x;
    }                  
    int y = (rand() % 2 * rooms_height);
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
        if(x < vec_width - 2) {                
            if(labyrinth[x + 2][y] == 1)      
                neighs.push_back(std::make_pair(x + 2, y));
        }
        if(y > 1) {                         
            if(labyrinth[x][y - 2] == 1)      
                neighs.push_back(std::make_pair(x, y - 2));
        }
        if(y < vec_height - 2) {                
            if(labyrinth[x][y + 2] == 1)      
                neighs.push_back(std::make_pair(x, y + 2));
        }

        if(!neighs.empty()) {
            int neighbor = rand() % neighs.size();
            int new_x = neighs[neighbor].first;
            int new_y = neighs[neighbor].second;
            labyrinth[(x + new_x) / 2][(y + new_y) / 2] = 0;
            walls -= 2;
            ++rooms;
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

    std::cout << walls << '/' << rooms << std::endl;

    for(int i = 2; i < vec_width - 1; i += 2) {
        for(int j = 2; j < vec_height - 1; j += 2) {
            labyrinth[i][j] = 2;                        //on odd x odd places are wall intersections(number 2)
        }
    }

    //CORNER TILES
    labyrinth[0][0] = 2;
    labyrinth[0][vec_height - 1] = 2;
    labyrinth[vec_width - 1][0] = 2;
    labyrinth[vec_width - 1][vec_height - 1] = 2;

    // CREATING LOOPS
    for(int i = 0; i < walls / 3; ++i) {
        while(true) {
            int x = rand() % (vec_width - 2) + 1;
            int y = rand() % (vec_height - 2) + 1;
            if(x % 2 == 0) {
                if(y % 2 == 0) {
                    y = y + 1;
                }
            } else {
                while(y % 2 != 0) {
                    y = (y + 1) % (vec_width - 2);
                }
            }

            if(labyrinth[x][y] == 1) {
                labyrinth[x][y] = 0;
                break;
            }
        }
    }

    std::cout << "exits are creating\n";

    //CREATING EXITS
    {
        int x = 0;
        int y = 0;
        int side;

        enum
        {
            TOP,
            RIGHT,
            BOTTOM,
            LEFT
        };

        while (exits_count > 0)
        {
            side = rand() % 4;
            switch (side)
            {
            case TOP:
                x = (rand() % (vec_width - 2)) + 1;
                if(x % 2 == 0) {
                    ++x;
                }
                y = 0;
                break;
            case RIGHT:
                x = vec_width - 1;
                y = (rand() % (vec_height - 2)) + 1;
                if(y % 2 == 0) {
                    ++y;
                }
                break;
            case BOTTOM:
                x = (rand() % (vec_width - 2)) + 1;
                if(x % 2 == 0) {
                    ++x;
                }
                y = vec_height - 1;
                break;
            case LEFT:
                x = 0;
                y = (rand() % (vec_height - 2)) + 1;
                if(y % 2 == 0) {
                    ++y;
                }
                break;
            }

            for(auto ex: exits) {
                if(abs(ex.first - x) + abs(ex.second - y) < std::min(vec_height, vec_width) / 2) {
                    int x_direction = 0;
                    int y_direction = 0;
                    bool move_x = false;
                    switch(side)
                    {
                        case TOP:
                            move_x = true;
                            if(ex.first - x < 0) {      //out new exit is on the right
                                x_direction = 2;
                                y_direction = 2;
                            }
                            else {
                                x_direction = -2;
                                y_direction = 2;
                            }
                            break;
                        case RIGHT:
                            move_x = false;
                            if(ex.second - y < 0) {      //out new exit is on the bottom
                                x_direction = -2;
                                y_direction = 2;
                            }
                            else {
                                x_direction = -2;
                                y_direction = -2;
                            }
                            break;
                        case BOTTOM:
                            move_x = true;
                            if(ex.first - x < 0) {
                                x_direction = 2;
                                y_direction = -2;
                            }
                            else {
                                x_direction = -2;
                                y_direction = -2;
                            }
                            break;
                        case LEFT:
                            move_x = false;
                            if(ex.second - y < 0) {
                                x_direction = 2;
                                y_direction = 2;
                            }
                            else {
                                x_direction = 2;
                                y_direction = -2;
                            }
                            break;
                    }
                    while(abs(ex.first - x) + abs(ex.second - y) < std::min(vec_height, vec_width) / 2) {
                        if(move_x) {
                            x += x_direction;
                            if(x <= 1) {
                                x = 0;
                                if(side == TOP)
                                    y = 1;
                                else
                                    y = vec_height - 2;
                                move_x = false;
                            }
                            else if(x >= vec_width - 2) {
                                x = vec_width - 1;
                                if(side == TOP)
                                    y = 1;
                                else
                                    y = vec_height - 2;
                                move_x = false;
                            }
                        }
                        else {
                            y += y_direction;
                            if(y <= 1) {
                                y = 0;
                                if(side == RIGHT)
                                    x = vec_width - 1;
                                else
                                    x = 1;
                                move_x = true;
                            }
                            else if(y >= vec_height - 2) {
                                y = vec_height - 1;
                                if(side == RIGHT)
                                    x = vec_width - 1;
                                else
                                    x = 1;
                                move_x = true;
                            }
                        }
                    }
                }
            }

            exits.push_back(std::make_pair(x, y));
            labyrinth[x][y] = 0;
            --exits_count;
        }
    }
    
}

void Labyrinth::draw()
{
    int wall = 0;

    for(int y = 0; y < vec_height; ++y) {
        for(int x = 0; x < vec_width; ++x) {
            if(labyrinth[x][y] == 0) {
                std::cout << ' ';
            }
            else if(labyrinth[x][y] == 2) {
                std::cout << '+';
            }
            else {
                if(x == 0 || x == vec_width - 1 || y % 2 != 0) {
                    std::cout << '|';
                    if(x > 0 && x < vec_width - 1)
                        ++wall;
                }
                else {
                    std::cout << '-';
                    if(y > 0 && y < vec_height - 1)
                        ++wall;
                }
            }
        }

        std::cout << std::endl;
    }

    std::cout << wall << std::endl;
}
