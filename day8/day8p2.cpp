#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

using namespace std;

struct Coord {
    size_t x;
    size_t y;

    Coord(size_t x, size_t y)
        : x(x), y(y) 
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
    Coord max_views_coord = Coord(0,0);
    int max_views = 1;

    //Initialize Tree Coords with 0 as the accumulator of tree views
    unordered_map<Coord, int> tree_coords{};
    for (auto x=0; x<trees.size(); x++)
    {
        for (auto y=0; y<trees.size(); y++)
        {
            tree_coords.emplace(Coord(x,y), 0);
        }
    }

    // loop through each tree
    for (auto& curr_tree: tree_coords) {
        int total = 1;
        int l_total{};
        size_t tree_height = trees[curr_tree.first.y][curr_tree.first.x] ;

        // check left
        for (signed x=curr_tree.first.x-1; x>=0; x--)
        {
            // if tree < tree_height then add to total
            if (trees[curr_tree.first.y][x] < tree_height)
            {
                l_total += 1; 
            }
            else
            {
                l_total += 1;
                break;
            }
        }
        total *= l_total;
        l_total = 0;
        // check right
        for (signed x=curr_tree.first.x+1; x < trees.size(); x++)
        {
            // if tree < tree_height then add to total
            if (trees[curr_tree.first.y][x] < tree_height)
            {
                l_total += 1; 
            }
            else
            {
                l_total += 1;
                break;
            }
        }
        total *= l_total;
        l_total = 0;
        // check up
        for (signed y=curr_tree.first.y-1; y >= 0; y--)
        {
            // if tree < tree_height then add to total
            if (trees[y][curr_tree.first.x] < tree_height)
            {
                l_total += 1; 
            }
            else
            {
                l_total += 1;
                break;
            }
        }
        total *= l_total;
        l_total = 0;

        // check down
        for (signed y=curr_tree.first.y+1; y < trees.size(); y++)
        {
            // if tree < tree_height then add to total
            if (trees[y][curr_tree.first.x] < tree_height)
            {
                l_total += 1; 
            }
            else
            {
                l_total += 1;
                break;
            }
        }
        total *= l_total;
        l_total = 0;

        curr_tree.second = total;
        // check if current tree has more views than max_views
        if (curr_tree.second > max_views)
        {
            max_views = curr_tree.second;
            max_views_coord = curr_tree.first;
        }

    }

    for (const auto& c : tree_coords) {
        cout << "x: " << c.first.x << ", y: " << c.first.y << ": " << c.second << endl;
    }

    cout << "Max Views: " << max_views << endl;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // Test Input
    //const string test_input = "30373\n25512\n65332\n33549\n35390";
    //istringstream stream(test_input);

    //// convert to vector of strings
    //vector<string> lines{};
    //for (string l; getline(stream,l);)
    //{
        //lines.push_back(l);
    //}

    // Real Input
    vector<string> lines{};
    string str{};
    while (getline(in, str))
    {
        lines.push_back(str);
    }

    countTrees(lines);

    return 0;
}