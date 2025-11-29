#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cstdint>
#include <unordered_map>
#include <tuple>
#include <regex>

struct Valve {
    std::string name;
    int flow;

    Valve(std::string name, int flow) : name(name), flow(flow) {}

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

void print_tunnels(std::unordered_map<std::string, std::tuple<int, std::vector<std::string>>>& tunnels)
{
    std::cout << "Printing Tunnels\n";
    for (auto& t : tunnels)
    {
        const auto& name = t.first;
        const auto& entry = t.second;
        std::cout << "(" << name << ") : ( " << std::get<0>(entry) << ", [ ";
        for (const auto& s : std::get<1>(entry))
        {
            std::cout << s << " ";
        }
        std::cout << "])\n";
    }
}

void parse_input(std::string input)
{
    std::regex pattern(R"([A-Z]{2})");
    
    std::istringstream stream(input);
    std::vector<std::string> lines{};
    std::string str{};
    while(getline(stream,str))
    {
        lines.push_back(str);
    }
    
    std::unordered_map<std::string, std::tuple<int, std::vector<std::string>>> tunnels{};
    for (auto& line : lines)
    {
        std::vector<std::string> results;
        
        auto w_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto w_end = std::sregex_iterator();
        
        for(std::sregex_iterator i = w_begin; i != w_end; ++i)
        {
            std::smatch match = *i;
            results.push_back(match.str());
        }

        if (results.empty()) continue;

        // parse flow rate (find '=' and check max 2 digits after);
        int flow = 0;
        auto flow_id = line.find('=');
        if (flow_id != std::string::npos) {
            ++flow_id;
            for (int i = flow_id; i <= static_cast<int>(flow_id) + 1 && i < static_cast<int>(line.size()); ++i)
            {
                if (std::isdigit(static_cast<unsigned char>(line[i])))
                {
                    flow *= 10;
                    flow += line[i] - '0';
                }
            }
        }

        // push data to tunnel map using valve name as key
        const std::string name = results[0];
        tunnels.emplace(name, std::make_tuple(flow, std::vector<std::string>{}));

        for (size_t i = 1; i < results.size(); ++i)
        {
            // push to current
            std::get<1>(tunnels[name]).push_back(results[i]);
        }
    }

    print_tunnels(tunnels);
}

int main(int argc, char** argv)
{
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    std::string test_input = R"(Valve AA has flow rate=0; tunnels lead to valves DD, II, BBI
Valve BB has flow rate=13; tunnels lead to valves CC, AA
Valve CC has flow rate=2; tunnels lead to valves DD, BB
Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
Valve EE has flow rate=3; tunnels lead to valves FF, DD
Valve FF has flow rate=0; tunnels lead to valves EE, GG
Valve GG has flow rate=0; tunnels lead to valves FF, HH
Valve HH has flow rate=22; tunnel leads to valve GG
Valve II has flow rate=0; tunnels lead to valves AA, JJ
Valve JJ has flow rate=21; tunnel leads to valve II)";

    // Test Input
    // std::istringstream stream(test_input);
    // std::vector<std::string> lines{};
    // std::string str{};
    // while(getline(stream,str))
    // {
        // lines.push_back(str);
    // }

    // Create Map Data
    // ('Name', flow) : list of connected tunnels
    // ('AA', 0) : ['DD', 'II', 'BB']
    std::unordered_map<std::string, std::tuple<int, std::vector<std::string>>> valves{};
    parse_input(test_input);

    // Find most efficient route

    // Real Input

    return 0;
}