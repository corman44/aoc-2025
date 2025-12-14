#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/// @brief Present contains a 2d bool vec of the present layout and the len x width
struct Present {
    vector<vector<bool>> layout;
    size_t length=3,width=3,count;
};

/// @brief Region contains a list of present requirmenets and the length x width of the space to fit them
struct Region {
    vector<size_t> presents_req;
    size_t length, width;
};

size_t str_to_int(string str)
{
    size_t num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

/// @brief Parse Input for list of Presents and list of Regions
/// @param lines vec of string for each line
/// @return 
tuple<vector<Present>, vector<Region>> parse_input(vector<string> lines)
{
    vector<Present> presents{};
    vector<Region> regions{};

    bool presents_done = false;

    size_t present_idx = 0;
    size_t present_line = 0;
    size_t layout_idx = 0;

    for (const auto& line: lines) {
        if (line.empty()) {
            // new present or end of presents
            present_idx += presents_done ? 0 : 1;
            continue;
        }

        if (line.find('x') != string::npos) {
            // parse tree present layout
            presents_done = true;

            const auto split = line.find('x');
            const auto col = line.find(':');
            const auto first_str = line.substr(0,split-1);
            const auto sec_str = line.substr(split+1, col - split - 1 );

            const auto first = str_to_int(first_str);
            const auto sec = str_to_int(sec_str);

            layout_idx++;
            continue;
        }

        if (line[1] == ':') {
            // present number lines can be skipped
            continue;
        }

        // otherwise we are parsing lines in a specific present
        if (presents.size() != present_idx + 1) {
            presents.push_back(Present{});
            present_line = 0;
            presents[present_idx].layout.resize(present_idx + 1);
        }

        for (const auto &c : line)
        {
            if (presents[present_idx].layout.size() != present_line + 1) {
                presents[present_idx].layout.resize(present_line + 1);
            }

            switch (c)
            {
            case '#':
                presents[present_idx].layout[present_line].push_back(true);
                ++presents[present_idx].count;
                break;
            default:
                presents[present_idx].layout[present_line].push_back(false);
            }
        }
        ++present_line;
    }

    return make_tuple(presents, regions);
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

    auto res = parse_input(lines);

    return 0;
}