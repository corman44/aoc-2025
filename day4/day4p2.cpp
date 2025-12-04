#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Cell{
    size_t x;
    size_t y;
};

struct Map{
    vector<vector<bool>> map;
};

Map parse_input(vector<string> lines)
{
    Map map{};
    for (size_t y=0; y<lines.size(); ++y)
    {
        map.map.emplace_back();
        for(size_t x=0; x<lines[0].size();++x)
        {
            lines[y][x] == '@' ? map.map[y].emplace_back(true) : map.map[y].emplace_back(false);
        }
    }

    return map;
}

bool roll_accessible(Map& map, Cell cell)
{
    int adj_rolls{};
    // < 4 rolls in adjacent 8 cells
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            //skip current roll
            if(x == 0 && y == 0)
            {
                continue;
            }
            int x_check = x + cell.x;
            int y_check = y + cell.y;

            //check boundaries
            if (y_check < 0 || y_check >= map.map.size() || x_check < 0 || x_check >= map.map[0].size())
            {
                continue;
            }
            else if (map.map[y_check][x_check])
            {
                adj_rolls++;
                //removed_paper.push_back(Cell{(size_t)x_check,(size_t)y_check});
            }
        }
    }
    return adj_rolls < 4;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    vector<string> input{};
    string str{};
    while (getline(in,str))
    {
        input.push_back(str);
    }
    
    auto map = parse_input(input);
    vector<Cell> removed_paper{};
    int total = 0;
    int last_count = 1;

    while(last_count > 0)
    {
        //reset count
        last_count = 0;

        for(size_t y=0;y<map.map.size();++y)
        {
            for(size_t x=0;x<map.map[0].size();++x)
            {
                if (map.map[y][x] && roll_accessible(map, Cell{x,y}))
                {
                    last_count++;
                    removed_paper.push_back(Cell{x,y});
                }
            }
        }

        //remove accessible
        for(auto& towel: removed_paper)
        {
            map.map[towel.y][towel.x] = false;
        }
        removed_paper.clear();

        total += last_count;
    }

    cout << "Total Accessible: " << total << endl;
    // Test input should result in 13 Rolls accessible

    return 0;
}