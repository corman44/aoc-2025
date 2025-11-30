#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum Pattern {
    ASH,
    ROCK,
};

struct PatternMap
{
    vector<vector<Pattern>> maps;
};

vector<PatternMap> parse_input(const vector<string>& text)
{
    vector<PatternMap> result{};
    result.resize(1);

    // loop through each line (if line is empty)
    size_t pattern_idx = 0;
    for (const auto& line : text)
    {
        // check if map is over (empty separator line)
        if (line.empty())
        {
            ++pattern_idx;
            if (pattern_idx >= result.size()) result.emplace_back();
            continue;
        }

        //if (pattern_idx >= result.size()) result.emplace_back();

        // build a row for this line
        vector<Pattern> row;
        for (const auto& c : line)
        {
            if (c == '#')
            {
                row.push_back(ASH);
            }
            else if (c == '.')
            {
                row.push_back(ROCK);
            }
            else
            {
                cout << "ERROR PARSING (unknown char): " << c << " in line: " << line << "\n";
            }
        }

        result[pattern_idx].maps.push_back(std::move(row));
    }

    return result;
}

int main(int argc, char** argv) {
    string path = (argc > 1) ? argv[1] : "input.txt";
    ifstream in(path);
    if (!in) {
        cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    string test_input = R"(#.##..##.
..#.##.#.
##......#
##......#
..#.##.#.
..##..##.
#.#.##.#.

#...##..#
#....#..#
..##..###
#####.##.
#####.##.
..##..###
#....#..#)";

    vector<string> lines{};
    istringstream stream(test_input);
    string temp{};
    while (getline(stream, temp))
    {
        lines.push_back(temp);
    }

    auto parsed = parse_input(lines);



    return 0;
}