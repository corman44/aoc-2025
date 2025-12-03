#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

uint64_t str_to_int(string str)
{
    uint64_t num=0;
    for(uint64_t i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

//need to check largest value X from the end of the
uint64_t recur_joltage(string jolts, uint64_t rem_dig, uint64_t num_so_far)
{
    //base case
    if (rem_dig == 0)
    {
        return num_so_far;
    }

    //shift digs left
    uint64_t update_num = num_so_far * 10;
    // find next largest dig
    uint64_t num_idx{};
    uint64_t largest{};
    for(uint64_t i = 0; i < jolts.length() - rem_dig + 1 ; ++i)
    {
        if (jolts[i] - '0' > largest)
        {
            largest = jolts[i] - '0';
            num_idx = i;
        }
    }
    update_num += largest;
    return recur_joltage(jolts.substr(num_idx + 1), rem_dig - 1, update_num);
}

uint64_t calculate_joltage(vector<string> jolt_rows)
{
    uint64_t sum{};

    //find largest value (and it's position) then find the next largest value to it's right
    for(auto& jolts: jolt_rows)
    {
        char largest{};
        for(uint64_t i = 0; i < jolts.length()-1;++i)
        {
            largest = jolts[i] > largest ? jolts[i] : largest;
        }
        size_t large_loc = jolts.find(largest);
        char second{};
        for(uint64_t i = large_loc+1; i < jolts.length(); ++i)
        {
            second = jolts[i] > second ? jolts[i] : second;
        }

        string number = {largest, second};
        cout << "Largest 2 Jolts = " << number << endl;
        sum += str_to_int(number);
    }

    return sum;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // Using Example input
    //string input = R"(987654321111111
//811111111111119
//234234234234278
//818181911112111)";

    //istringstream stream(input);
    //string str{};
    //vector<string> lines{};
    //while(getline(stream, str))
    //{
        //lines.push_back(str);
    //}

    //uint64_t total_jolts{};
    //for (auto& line: lines)
    //{
        //total_jolts += recur_joltage(line, 12, 0);
    //}
    //cout << "Total Jolts = " << total_jolts <<endl;

    // Using Real input
    vector<string> input{};
    string str{};
    while (getline(in,str))
    {
        input.push_back(str);
    }

    uint64_t total_jolts{};
    for (auto& line: input)
    {
        total_jolts += recur_joltage(line, 12, 0);
    }
    cout << "Total Jolts = " << total_jolts <<endl;
    
    return 0;
}