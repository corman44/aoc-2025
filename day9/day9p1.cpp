#include <cstdint>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Coord {
    int64_t row,col;
};

bool operator==(const Coord& c1, const Coord& c2) {
    return c1.row == c2.row && c1.col == c2.col;
}

int64_t str_to_int(string str)
{
    int64_t num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

//int64_t euclidian_dist(const Coord& c1, const Coord& c2) {
    //int64_t num1 = c1.col - c2.col;
    //int64_t num2 = c1.row - c2.row;
    //return sqrt(pow(num1, 2) + pow(num2, 2));
//}

vector<Coord> parse_input(vector<string> lines)
{
    vector<Coord> coords;
    for(auto& line: lines) {
        auto splitter = line.find(',');

        coords.push_back(Coord{str_to_int(line.substr(splitter+1)), str_to_int(line.substr(0,splitter))});
    }

    return coords;
}

int64_t inclusive_area(const Coord& c1, const Coord& c2) {
    return (abs(c1.col - c2.col) + 1) * (abs(c1.row - c2.row) + 1);
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
    int64_t big_area{};
    tuple<Coord,Coord> far_coords{};
    for(const auto& c1: coords) {
        for (const auto& c2: coords) {
            if (c1 == c2 || c1.row == c2.row || c1.col == c2.col) {
                continue;
            }
            if (inclusive_area(c1,c2) > big_area) {
                big_area = inclusive_area(c1,c2);
                far_coords = make_tuple(c1,c2); 
            }
        }
    }

    return 0;
}
// winner: 4725826296

// wrong:   4725759204
// too low: 4472808582, 4472727908
// too high: 18446744073709549568