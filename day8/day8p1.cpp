#include <cstdint>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Vec3 {
    uint16_t X;
    uint16_t Y;
    uint16_t Z;
};

uint16_t str_to_int(string str)
{
    int num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

vector<Vec3> parse_input(vector<string> lines)
{
    vector<Vec3> coords{};
    // 3 numbers, comma seperated
    for (const auto& line: lines) {
        auto end_first = line.find(',');
        auto end_second = line.find(',', end_first+1);

        auto first_num = str_to_int(line.substr(0, end_first));
        auto sec_num = str_to_int(line.substr(end_first+1, end_second-end_first-1));
        auto third_num = str_to_int(line.substr(end_second+1));

        coords.push_back(Vec3{first_num,sec_num,third_num});
    }

    return coords;
}

uint16_t euclid_distance(Vec3 first, Vec3 sec) {
    uint16_t dist = sqrt(pow(first.X - sec.Y, 2) + pow(first.Y - sec.Y, 2) + pow(first.Z - sec.Z, 2));
    return dist;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "test.txt";
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

    uint16_t shortest = 0xFFFF;
    Vec3 short1{};
    Vec3 short2{};

    for(int i=0; i< coords.size(); ++i) {
        for (int j=0; j<coords.size(); ++j) {
            if (j==i) {
                continue;
            }
            
            auto dist = euclid_distance(coords[i], coords[j]);
            if (shortest > dist) {
                short1 = coords[i];
                short2 = coords[j];
                shortest = dist;
            }
        }
    }

    return 0;
}