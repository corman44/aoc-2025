#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/// @brief simple struct containing lights_status and num lights
struct Inidicator {
    uint16_t light_status{}, num_lights{}, light_goal{};
};


struct LightDiagram {
    Inidicator indicator{};
    vector<vector<size_t>> buttons{};
    //vector<size_t> jolts;
};

size_t str_to_int(string str)
{
    int num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

/// @brief apply's the button(s) provided to the provided light
/// @param lights 
/// @param pressed_buttons 
void push_button(Inidicator& lights, vector<size_t> pressed_buttons) {
    // XOR op with the specific bit shifted
    for(const auto& button: pressed_buttons ) {
        lights.light_status ^= (0x1 << lights.num_lights - 1 - button);
    }
}

/// @brief takes in a comma seperated string of numbers and returns a vec of ints
/// @param group_str 
/// @return 
vector<size_t> parse_group(string group_str) {
    vector<size_t> nums{};
    stringstream ss(group_str);
    string seg;

    while (getline(ss, seg, ',')) {
        nums.push_back(str_to_int(seg));
    }

    return nums;
}

vector<LightDiagram> parse_input(vector<string> lines)
{
    vector<LightDiagram> light_diagrams{};

    int idx = 0;

    for (const auto& line: lines) {
        stringstream ss_in(line);
        string group_token{};
        size_t jolts_start = line.find('{');
        light_diagrams.push_back(LightDiagram{});

        while (ss_in >> group_token) {

            size_t start = group_token.find('(');
            size_t end = group_token.find(')');

            if (group_token.find(']') != string::npos) {
                // parse lights
                size_t sq_end = group_token.find(']');

                auto group = group_token.substr(1, sq_end - 1);
                for (int i = 0; i < group.size(); ++i) {
                    if (group[i] == '#') {
                        light_diagrams[idx].indicator.light_goal ^= 0x1 << group.size() - 1 - i;
                    }
                    light_diagrams[idx].indicator.num_lights = group.size();
                }
                continue;
            }

            if (start >= jolts_start) {
                break;
            }
            string content = group_token.substr(start+1, end - start -1);

            if(content.find(',') != string::npos) {
                auto group = parse_group(content);
                light_diagrams[idx].buttons.push_back(group);
            } else {
                const auto group = vector<size_t>{str_to_int(content)};
                light_diagrams[idx].buttons.push_back(group);
            }

        }
        // append light_diagrams

        ++idx;
    }
    return light_diagrams;
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

    auto lds = parse_input(lines);

    return 0;
}