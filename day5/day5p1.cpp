#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>

using namespace std;

uint64_t str_to_int(string str)
{
    uint64_t num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

struct Range{
    uint64_t start;
    uint64_t end;
};

vector<Range> parse_input(vector<string> lines, vector<uint64_t>& ingredients)
{
    vector<Range> ranges{};
    int nl_found = 0;
    for(auto& line: lines)
    {
        if(line.empty())
        {
            nl_found = 1;
            continue;
        }

        if(nl_found == 0)
        {
            size_t dash = line.find('-');
            uint64_t first = str_to_int(line.substr(0,dash));
            uint64_t second = str_to_int(line.substr(dash+1));
            ranges.push_back(Range{first,second});
        }
        else {
            uint64_t num = str_to_int(line);
            ingredients.push_back(num);
        }
    }
    return ranges;
}

void merge_range(vector<Range>& ranges, int which)
{
    //check not last element
    if (which == ranges.size())
    {
        return;
    }

    // check overlap
    if (ranges[which].end > ranges[which+1].start)
    {
        ranges[which].end = ranges[which+1].end;

        //remove checked range
        ranges.erase(ranges.begin() + which + 1);

        //call again
        merge_range(ranges, which);
    } else {
        return;
    }
}

bool is_fresh(vector<Range>& ranges, uint64_t num)
{
    for(auto& range: ranges)
    {
        if(num >= range.start && num <= range.end)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
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
    
    // get parsed info
    vector<uint64_t> ingredients{};
    auto ranges = parse_input(lines,ingredients);

    // sort the ranges by lowest value
    //sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        //return a.start < b.start;
    //});

    //size_t pop_count{};
    //for(int i = 0; i < ranges.size()-1; ++i)
    //{
        //merge_range(ranges, i);
    //}

    int count = 0;
    for(auto& num: ingredients)
    {
        count += is_fresh(ranges, num) ? 1 : 0;
    }

    cout << count << endl;

    return 0;
}