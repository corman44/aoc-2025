#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>

using namespace std;

struct Coord {
    size_t x;
    size_t y;
    size_t val;

    Coord(size_t x, size_t y, size_t m)
        : x(x), y(y), val(m) 
    {}
    
    bool operator==(const Coord& p) const {
        return (this->x == p.x && this->y == p.y);
    }

};

namespace std {
    template <>
    struct hash<Coord> {
        size_t operator()(const Coord& p) const {
            auto h1 = hash<size_t>{}(p.x);
            auto h2 = hash<size_t>{}(p.y);

            return h1 ^ (h2 << 1);
        }
    };
}

void countTrees(const vector<string>& trees)
{
    uint32_t total{};
    unordered_set<Coord> tree_coords{};

    // looping left to right
    for (size_t x = 1; x < trees.size() - 1 ; x++ )
    {
        size_t curr_max = trees[x][0];

        for ( size_t y = 1; y < trees[x].size() - 1 ; y++)
        {
            if (curr_max == '9')
            {
                break;
            }
            if ( curr_max < trees[x][y])
            {
                curr_max = trees[x][y];
                tree_coords.insert(Coord(x, y, curr_max-'0'));
            }
        }
    }

    // Right to left
    for (size_t x = 1; x < trees.size() - 1 ; x++ )
    {
        size_t curr_max = trees[x][trees.size()-1];

        for ( size_t y = trees[x].size() - 2; y > 0 ; y--)
        {
            if (curr_max == '9')
            {
                break;
            }
            if ( curr_max < trees[x][y])
            {
                curr_max = trees[x][y];
                tree_coords.insert(Coord(x, y, curr_max-'0'));
            }
        }
    }

    // Top to bottom
    for (size_t x = 1; x < trees.size() - 1 ; x++ )
    {
        size_t curr_max = trees[0][x];

        for ( size_t y = 1; y < trees[x].size() - 1 ; y++)
        {
            if (curr_max == '9')
            {
                break;
            }
            if ( curr_max < trees[y][x])
            {
                curr_max = trees[y][x];
                tree_coords.insert(Coord(y, x, curr_max-'0'));
            }
        }
    }

    // Bottom to top
    for (size_t x = 1; x < trees.size() - 1 ; x++ )
    {
        size_t curr_max = trees[trees.size() - 1][x];

        for ( size_t y = trees[x].size() - 2 ; y > 0 ; y--)
        {
            if (curr_max == '9')
            {
                break;
            }
            if ( curr_max < trees[y][x])
            {
                curr_max = trees[y][x];
                tree_coords.insert(Coord(y, x, curr_max-'0'));
            }
        }
    }
    total = tree_coords.size();
    total += trees.size() * 2 + trees[0].size() * 2 - 4; 
    cout << "Total Count: " << total << endl;

    for (const auto& c : tree_coords) {
        cout << "x: " << c.x << ", y: " << c.y << ": " << c.val << endl;
    }
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // const string test_input = "30373\n25512\n65332\n33549\n35390";
    // istringstream stream(test_input);

    //convert to vector of strings
    //vector<string> lines{};
    //for (string l; getline(stream,l);)
    //{
        //lines.push_back(l);
    //}

    vector<string> lines{};
    string str{};
    while (getline(in, str))
    {
        lines.push_back(str);
    }

    countTrees(lines);

    return 0;
}