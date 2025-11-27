#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <unordered_map>
#include <regex>

using namespace std;

struct Valve {
    string name;
    int flow;
    bool operator==(Valve const& other) const noexcept {
        return name == other.name && flow == other.flow;
    }
};

namespace std {
    template<>
    struct hash<Valve> {
        size_t operator()(Valve const& v) const noexcept
        {
            return std::hash<std::string>{}(v.name) ^ (std::hash<int>{}(v.flow) << 1);
        }
    };
}

void parse_input(vector<string> input)
{
    unordered_map<Valve, vector<string>> tunnels{};
    regex flex_patter(R"(([A-Z]{2})\s\1)");
    string str{};
    for (auto itr=input.begin(); itr!=input.end(); itr++)
    {
        itr->
    }
}

int main(int argc, char** argv)
{
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    string test_input = R"(Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
Valve BB has flow rate=13; tunnels lead to valves CC, AA
Valve CC has flow rate=2; tunnels lead to valves DD, BB
Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
Valve EE has flow rate=3; tunnels lead to valves FF, DD
Valve FF has flow rate=0; tunnels lead to valves EE, GG
Valve GG has flow rate=0; tunnels lead to valves FF, HH
Valve HH has flow rate=22; tunnel leads to valve GG
Valve II has flow rate=0; tunnels lead to valves AA, JJ
Valve JJ has flow rate=21; tunnel leads to valve II)";
    //cout << test_input << endl;

    // Test Input
    istringstream stream(test_input);
    vector<string> lines{};
    string str{};
    while(getline(stream,str))
    {
        lines.push_back(str);
    }

    // Create Map Data
    // ('Name', flow) : list of connected tunnels
    // ('AA', 0) : ['DD', 'II', 'BB']
    unordered_map<Valve, vector<string>> valves{};
    parse_input(lines);

    // Find most efficient route

    // Real Input

    return 0;
}