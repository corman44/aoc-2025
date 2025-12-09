#include <cstdint>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

// [ ] find largest distance between 2 points

using namespace std;

struct Coord {
    uint64_t row,col;
};

bool operator==(const Coord& c1, const Coord& c2) {
    return c1.row == c2.row && c1.col == c2.col;
}

uint64_t str_to_int(string str)
{
    uint64_t num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

uint64_t euclidian_dist(const Coord& c1, const Coord& c2) {
    return sqrt(pow(c1.col - c2.col, 2) + pow(c1.row - c2.row,2));
}

vector<Coord> parse_input(vector<string> lines)
{
    vector<Coord> coords;
    for(auto& line: lines) {
        auto splitter = line.find(',');

        coords.push_back(Coord{str_to_int(line.substr(splitter+1)), str_to_int(line.substr(0,splitter))});
    }

    return coords;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    vector<string> lines{};
    string str{};
    while (getline(in,str))
    {
        lines.push_back(str);
    }

    auto coords = parse_input(lines);
    uint64_t far_dist{};
    tuple<Coord,Coord> furthest{};
    for(const auto& c1: coords) {
        for (const auto& c2: coords) {
            if (c1 == c2) {
                continue;
            }
            if (euclidian_dist(c1,c2) > far_dist) {
                far_dist = euclidian_dist(c1,c2);
                furthest = make_tuple(c1,c2); 
            }
        }
    }

    auto largest = (sqrt(pow(get<0>(furthest).row - get<1>(furthest).row, 2)) + 1) * (sqrt(pow((get<0>(furthest).col - get<1>(furthest).col),2)) + 1);

    return 0;
}

// too low: 4472808582
// too high: 18446744073709549568