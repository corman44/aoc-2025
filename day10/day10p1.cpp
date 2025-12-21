#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/// @brief simple struct containing lights_status and num lights
struct Inidicator {
    uint16_t  light_status{}, num_lights{}, light_goal{};
};


struct LightDiagram {
    Inidicator indicator{};
    vector<vector<uint16_t>> buttons{};
    //vector<uint16_t> jolts;
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

/// @brief apply's the button(s) provided to the provided light
/// @param lights 
/// @param pressed_buttons 
uint16_t push_button(const uint16_t & lights, const vector<uint16_t>& pressed_button, uint16_t light_len) {
    uint16_t  ans = lights;
    // XOR op with the specific bit shifted
    for (const auto& each: pressed_button) {
        ans ^= (0x1 << light_len - 1 - each);
    }

    return ans;
}

/// @brief takes in a comma seperated string of numbers and returns a vec of ints
/// @param group_str 
/// @return 
vector<uint16_t> parse_group(string group_str) {
    vector<uint16_t> nums{};
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
        uint16_t jolts_start = line.find('{');
        light_diagrams.push_back(LightDiagram{});

        while (ss_in >> group_token) {

            uint16_t start = group_token.find('(');
            uint16_t end = group_token.find(')');

            if (group_token.find(']') != string::npos) {
                // parse lights
                uint16_t sq_end = group_token.find(']');

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
                const auto group = vector<uint16_t>{str_to_int(content)};
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
    vector<uint16_t> min_presses{};

    unordered_set<uint16_t > last_set{};
    
    for (auto& ld: lds) {
        
        // stop while loop when the goal matches the current light's status
        bool goal_match = false;
        uint16_t presses = 1;
        unordered_set<uint16_t > curr_set{};
        uint16_t  num;

        // initialize last set
        for (auto& l: ld.buttons) {
            last_set.insert(push_button(0, l, 5));
        }

        while(!goal_match) {
            ++presses;

            for (auto& state: last_set) {
                curr_set.emplace(state);
            }

            // keep traversing all paths (with BFS) until we find a match
            for (auto& curr: last_set) {
                for (auto& button: ld.buttons) {
                    uint16_t  num = push_button(curr, button, ld.indicator.num_lights);
                    curr_set.emplace(num);
                }
            }
            
            // check if match found
            goal_match = curr_set.find(ld.indicator.light_goal) != curr_set.end();

            last_set = curr_set;
            curr_set.clear();
        }

        min_presses.push_back(presses);
    }

    cout << "All Min Presses: ";

    auto sum = 0;
    for (const auto& press: min_presses) {
        sum += press;
        cout << press << " ";
    }

    cout << endl << "Sum = " << sum << endl;

    return 0;
}