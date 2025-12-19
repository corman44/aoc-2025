#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Data Types:
//  - Server Output = map<server, vec<servers>>
//  - Path = vector<string>

struct ServerData
{
    unordered_set<string> outputs;

};

struct Graph2D
{
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addNode(const string& node) {
        if (adjList.find(node) == adjList.end()) {
            adjList[node] = {};
        }
    }

    bool addConnection(const string& node, const string& conn) {
        if (adjList.find(conn) == adjList.end()) {
            return false;
        }

        adjList[conn].push_back(conn);
    }

    vector<string> getConnections(const string& node) {
        return adjList[node];
    }
};

unordered_map<string, ServerData> parse_input(vector<string> lines)
{
    unordered_map<string, ServerData> servers{};
    for (const auto &line : lines)
    {
        const auto colon = line.find(':');
        stringstream ss(line.substr(colon + 2));
        string sub;

        const auto key = line.substr(0, 3);
        vector<string> empty_vec_str{};

        servers[key] = ServerData{};

        while (ss >> sub)
        {
            servers[key].outputs.emplace(sub);
        }
    }

    return servers;
}

int main(int argc, char **argv)
{
    std::string path = (argc > 1) ? argv[1] : "test.txt";
    std::ifstream in(path);
    if (!in)
    {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    vector<string> lines{};
    string str{};
    while (getline(in, str))
    {
        lines.push_back(str);
    }

    unordered_map<string, ServerData> servers{};
    servers = parse_input(lines);

    // BFS of all servers
    // Starting point is "you"

    bool done = false;
    vector<string> paths;
    int path_totals = 0;

    // init starting outputs (from "you")
    for (const auto& output: servers["you"].outputs) {
        paths.push_back(output);
    }

    while(!done) {

        for (auto& path: paths) {
            //gather outputs from this name
            if (servers[path].outputs.contains("out")) {
                // add one to found paths
                path_totals += 1;
            }
        }
    }

    return 0;
}