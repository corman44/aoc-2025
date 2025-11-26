#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;


optional<uint32_t> getNum(const string& line, size_t& i, char end)
{
    uint32_t num{};
    // check each char until end char or max digits
    constexpr const size_t maxDigits{3};
    const auto imax = i + maxDigits;
    while (i<imax) {
        if (isdigit(line[i]) != 0)
        {
            num *= 10; // shift digits left
            num += line[i++] - '0';
            continue;
        }
        break;
    }
    return line[i] == end ? num : optional<uint32_t>();
}

uint64_t count(const string &line, bool &enabled)
{
    uint64_t sum = 0;
    size_t i{};
    while (i < line.size() - 8)
    {

        if ( line[i] == 'd' && line[i+1] == 'o' && line[i+2] == '(' && line[i+3] == ')')
        {
            enabled = true;
        }
        if ( line[i] == 'd' && line[i+1] == 'o' && line[i+2] == 'n' && line[i+3] == '\'' && line[i+4] == 't' && line[i+5] == '(' && line[i+6] == ')')
        {
            enabled = false;
        }

        if (enabled) {
            if (line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '(')
            {
                // check nums exist until ',' and between ',' and ')'
                i += 4;

                const auto first = getNum(line, i, ',');
                if (!first.has_value())
                {
                    continue;
                }
                //cout << "First: " << first.value() << endl;

                i++; // jump over ',' for second number

                const auto second = getNum(line, i, ')');
                if (!second.has_value())
                {
                    continue;
                }
                //cout << "Second: " << second.value() << endl;
                sum += first.value() * second.value();
            }
        }
        i++;
    }
    return sum;
}

// read lines from file into provided lines vector
static bool readFile(const string &fileName, vector<string> &lines) {
    ifstream in {fileName};
    if (!in) {
        cerr << "Cannot open file " << fileName << endl;
        return false;
    }

    string str;
    while (getline(in, str))
    {
        lines.push_back(str);
    }
    return true;
}

int main(int argc, char** argv) {
    string path = (argc > 1) ? argv[1] : "input.txt";
    ifstream in(path);
    if (!in) {
        cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // string test_input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
    // cout << "Total Count: " << count(test_input) << endl;

    // Part1
    // uint64_t sum{};
    // string str{};
    // while(getline(in,str))
    // {
        // sum += count(str);
    // }
    // cout << "Total: " << sum << endl;

    bool enabled = true;

    // Part2
    uint64_t sum{};
    string str{};
    while(getline(in,str))
    {
        sum += count(str, enabled);
    }
    cout << "Total: " << sum << endl;

    return 0;
}