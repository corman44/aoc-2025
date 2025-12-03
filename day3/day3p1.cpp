#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int str_to_int(string str)
{
    int num=0;
    for(int i = 0; i < str.length(); ++i)
    {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

int calculate_joltage(vector<string> jolt_rows)
{
    int sum{};

    //find largest value (and it's position) then find the next largest value to it's right
    for(auto& jolts: jolt_rows)
    {
        char largest{};
        for(int i = 0; i < jolts.length()-1;++i)
        {
            largest = jolts[i] > largest ? jolts[i] : largest;
        }
        size_t large_loc = jolts.find(largest);
        char second{};
        for(int i = large_loc+1; i < jolts.length(); ++i)
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
    //int total_jolts = calculate_joltage(lines);
    //cout << "Total Jolts = " << total_jolts <<endl;

    // Using Real input
    vector<string> input{};
    string str{};
    while (getline(in,str))
    {
        input.push_back(str);
    }
    int total_jolts = calculate_joltage(input);
    cout << "Total Jolts = " << total_jolts <<endl;
    

    return 0;
}