#include "Labyrinth.h"
#include <vector>
#include <stack>
#include <queue>

Labyrinth::Labyrinth(unsigned height, unsigned width) : height(height), width(width), labyrinth(width * 2 + 1, std::vector<int>(height * 2 + 1, TILE_TYPES::WALL)), weightMap(height, std::vector<int>(width, -1))
{
}

void Labyrinth::init()
{
    addPaths();
    addLoops(100);
    addExits(1);
}

void Labyrinth::addPaths()
{
    std::stack<std::pair<int, int>> st;

    int x = (rand() % 2 * width);
    if (x % 2 == 0)
    {
        ++x;
    }
    int y = (rand() % 2 * height);
    if (y % 2 == 0)
    {
        ++y;
    }

    st.push(std::make_pair(x, y));

    while (!st.empty())
    {
        labyrinth[x][y] = 0;
        std::vector<std::pair<int, int>> neighs;

        if (x > 1)
        {
            if (labyrinth[x - 2][y] == TILE_TYPES::WALL)
                neighs.push_back(std::make_pair(x - 2, y));
        }
        if (x < 2 * width - 1)
        {
            if (labyrinth[x + 2][y] == TILE_TYPES::WALL)
                neighs.push_back(std::make_pair(x + 2, y));
        }
        if (y > 1)
        {
            if (labyrinth[x][y - 2] == TILE_TYPES::WALL)
                neighs.push_back(std::make_pair(x, y - 2));
        }
        if (y < 2 * height - 1)
        {
            if (labyrinth[x][y + 2] == TILE_TYPES::WALL)
                neighs.push_back(std::make_pair(x, y + 2));
        }

        if (!neighs.empty())
        {
            int neighbor = rand() % neighs.size();
            int new_x = neighs[neighbor].first;
            int new_y = neighs[neighbor].second;
            labyrinth[(x + new_x) / 2][(y + new_y) / 2] = TILE_TYPES::EMPTY;
            x = new_x;
            y = new_y;
            st.push(std::make_pair(x, y));
        }
        else
        {
            st.pop();
            if (!st.empty())
            {
                x = st.top().first;
                y = st.top().second;
            }
        }
    }
}

void Labyrinth::addLoops(unsigned short count)
{
    for (int i = 0; i < count; ++i)
    {
        while (true)
        {
            int x = rand() % (2 * width - 1) + 1;
            int y = rand() % (2 * height - 1) + 1;
            if (x % 2 == 0)
            {
                if (y % 2 == 0)
                {
                    y = y + 1;
                }
            }
            else
            {
                if (y % 2 != 0)
                {
                    y = (y + 1) % (2 * width - 1);
                }
            }

            if (labyrinth[x][y] == TILE_TYPES::WALL)
            {
                labyrinth[x][y] = TILE_TYPES::EMPTY;
                break;
            }
        }
    }
}

int distance(std::pair<int, int> a, std::pair<int, int> b)
{
    return (int)std::sqrt(std::pow((a.first - b.first), 2) + std::pow((a.second - b.second), 2));
}

void Labyrinth::addExits(unsigned short count)
{
    std::pair<int, int> location;
    int side;

    enum
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };

    while (count > 0)
    {
        side = rand() % 4;
        switch (side)
        {
        case TOP:
            location = std::make_pair(rand() % width, 0);
            break;
        case RIGHT:
            location = std::make_pair(width - 1, rand() % height);
            break;
        case BOTTOM:
            location = std::make_pair(rand() % width, height - 1);
            break;
        case LEFT:
            location = std::make_pair(0, rand() % height);
            break;
        }

        for (size_t i = 0; i < exits.size(); i++)
        {
            // todo:: (refactor) hard coded number, plus in some case if exit count is > 3 can break.
            if (distance(location, exits[i]) <= 10)
            {
                continue;
            }
        }

        exits.push_back(location);
        labyrinth[location.second][location.first] = TILE_TYPES::EXIT;
        --count;
    }
}

std::vector<std::vector<int>> Labyrinth::bfs(std::pair<int, int> startPoint)
{
    std::cout << "y = " << startPoint.second << " x = " << startPoint.first << '\n';
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<int>> distances(height, std::vector<int>(width, -1));

    std::queue<std::pair<int, int>> q;
    std::cout << "here" << std::endl;

    q.push({startPoint.first, startPoint.second});
    visited[startPoint.second][startPoint.first] = true;
    distances[startPoint.second][startPoint.first] = 0;

    std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (!q.empty())
    {
        std::pair<int, int> current = q.front();
        q.pop();

        for (const auto &dir : directions)
        {
            int y = current.first + dir.first;
            int x = current.second + dir.second;

            if (x >= 0 && x < width && y >= 0 && y < height &&
                !visited[y][x] && labyrinth[y * 2 + 1 + dir.second][x * 2 + 1 + dir.first] == 0)
            {
                visited[y][x] = true;
                distances[y][x] = distances[current.second][current.first] + 1;
                q.push({x, y});
            }
        }
    }

    return distances;
}

void Labyrinth::createWeightMap()
{
    for (const auto &exit : exits)
    {
        const auto exitBfs = bfs(exit);

        for (int i = 0; i < weightMap.size(); ++i)
        {
            for (int j = 0; j < weightMap[0].size(); ++j)
            {
                std::cout << exitBfs[i][j] << ' ';
            }

            std::cout << std::endl;
        }
    }

    // for (int i = 0; i < weightMap.size(); ++i)
    // {
    //     for (int j = 0; j < weightMap[0].size(); ++j)
    //     {
    //         std::cout << weightMap[i][j] << '\t';
    //     }
    //     std::cout << std::endl;
    // }
}
