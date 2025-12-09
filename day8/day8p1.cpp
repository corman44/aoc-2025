#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <sstream>
#include <string>
//#include <unordered_set>
#include <vector>

// Make 10 shortest connections. Answer is mutiplying 3 largest connection together

using namespace std;

struct Vec3 {
    uint32_t X;
    uint32_t Y;
    uint32_t Z;

    bool operator<(const Vec3& other) const {
        if (X != other.X) return X < other.X;
        if (Y != other.Y) return Y < other.Y;
        return Z < other.Z;
    }
};

struct PairDist {
    uint64_t dist;
    Vec3 v1;
    Vec3 v2;

    bool operator<(const PairDist& other) const {
        return dist < other.dist;
    }
};

void print_vec3(const Vec3& v) {
    cout << "X=" << v.X <<" Y=" << v.Y << " Z=" << v.Z;
}

class GraphVec3 {
public:
    set<Vec3> nodes {};
    map<Vec3, vector<Vec3>> adj_list;

    void add_connection(Vec3 v1, Vec3 v2) {
        // check that they both exist
        if (this->nodes.find(v1) == nodes.end() || this->nodes.find(v2) == nodes.end()) {
            cout << "ERROR: a node doesn't exist " << endl;
            print_vec3(v1);
            cout << endl;
            print_vec3(v2);
            cout << endl;
            return;
        }

        // add to eachother
        this->adj_list[v1].push_back(v2);
        this->adj_list[v2].push_back(v1);
    }
};

uint32_t str_to_int(string str)
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

uint32_t euclid_distance(Vec3 first, Vec3 sec) {
    uint32_t dist = sqrt(pow(first.X - sec.X, 2) + pow(first.Y - sec.Y, 2) + pow(first.Z - sec.Z, 2));
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

    uint32_t shortest = 0xFFFF;
    Vec3 short1{};
    Vec3 short2{};

    // Gather all PairDist
    // Measure all Distances (and store v1 & v2 for each)
    set<PairDist> node_distances;
    for(int i=0; i< coords.size(); ++i) {
        for (int j=0; j<coords.size(); ++j) {
            if (j==i) {
                continue;
            }
            auto dist = euclid_distance(coords[i], coords[j]);
            node_distances.emplace(PairDist{dist,coords[i],coords[j]});
        }
    }

    // go to 10 lowest and and connect them to eachother
    for (const auto& pd = node_distances.begin(); pd < node_distances.begin()) {

    }
    // then loop through all in adj_list and report top 3
    // mult top 3 together for result 

    return 0;
}