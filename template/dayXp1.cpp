#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // Using Example input
    string input = R"()";
    //formatting string to vector<string>
    //istringstream stream(input);
    //string str{};
    //vector<string> lines{};
    //while (getline(input,str))
    //{
        //lines.push_back(str);
    //}

    // Using Real input
    //vector<string> lines{};
    //string str{};
    //while (getline(in,str))
    //{
        //lines.push_back(str);
    //}

    return 0;
}