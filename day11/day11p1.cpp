#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Data Types:
//  - Server Output = map<server, vec<servers>>
//  - Path = vector<string>

struct ServerData {
    vector<string> outputs;
    vector<string> shortest_path;
};

unordered_map<string, ServerData> parse_input(vector<string> lines)
{
    unordered_map<string, ServerData> servers{};
    for (const auto& line: lines) {
        const auto colon = line.find(':');
        stringstream ss(line.substr(colon+2));
        string sub;

        const auto key = line.substr(0,3);
        vector<string> empty_vec_str{};

        servers[key] = ServerData{};

        while (ss >> sub) {
            servers[key].outputs.push_back(sub);
        }
    }

    return servers;
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

    unordered_map<string, ServerData> servers{};
    servers = parse_input(lines);

    return 0;
}