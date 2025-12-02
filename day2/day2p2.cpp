#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>

using namespace std;

struct Range {
    uint64_t start;
    uint64_t end;
};

int num_digits(uint64_t num)
{
    return (int)log10(num) + 1;
}

bool is_valid(uint64_t num, int x)
{
    auto str = to_string(num);
    auto len = str.length();

    // Check that len / x has no remainder
    if (len % x == 0)
    {
        for (int i = 0; i < (len / x) - 1; ++i)
        {
            auto first = str.substr(i*x, x);
            auto second = str.substr((i+1)*x, x);
            if (first != second)
            {
                return true;
            }
        }
        return false;
    } else {
        return true;
    }
}


vector<Range> parse_input(string input)
{
    vector<Range> ranges{};
    uint64_t tmp{};
    uint64_t idx{};

    // loop through each char (if '-' move to building end, if , build new range)
    ranges.push_back(Range{});
    for (auto c: input)
    {
        if (c == '-')
        {
            ranges[idx].start = tmp;
            tmp = 0;            
        }
        else if (c == ',')
        {
            ranges[idx].end = tmp;
            idx++;
            tmp = 0;
            ranges.push_back(Range{});
        }
        else 
        {
            tmp *= 10;
            tmp += c - '0';
        }
    }
    ranges[idx].end = tmp; // handling end of string case

    return ranges;
}

vector<uint64_t> gather_invalid_ids(vector<Range> ranges)
{
    vector<uint64_t> invalids{};
    for (auto& range: ranges)
    {
        for (auto num = range.start; num <= range.end; num++)
        {
            if(num_digits(range.start) > 3) {
                cout << "";
            }
            for(auto len = 1; len <= num_digits(num)/2; ++len)
            {
                if (!is_valid(num, len))
                {
                    invalids.push_back(num);
                    break;
                }
            }
        }
    }
    return invalids;
}


int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // Using Example input
    //string input = R"(11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124)";

    // Using Real input
    string input{};
    string str{};
    while (getline(in,str))
    {
        input.append(str);
    }

    auto ranges = parse_input(input);
    auto invalids = gather_invalid_ids(ranges);

    uint64_t sum{};
    for (auto& num: invalids)
    {
        sum += num;
    }

    // Testing Test
    //uint64_t ans1 = 1227775554;
    uint64_t ans = 4174379265;
    if (ans == sum)
    {
        cout << "Answer Found: " << sum << endl; 
    } else {
        cout <<"Wrong Answer: " << sum << " != " << ans << endl;
    }
    cout << "Sum Invalids: " << sum << endl;
    


    return 0;
}

// Attempts: 4444166768, 2520874495, 1034815904_low, 1034815904, 13919717792