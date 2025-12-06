#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cctype>
#include <tuple>

using namespace std;

enum Operand{
    Multiply,
    Add,
};

uint64_t add_all(const vector<uint64_t>& nums) {
    return accumulate(nums.begin(), nums.end(), (uint64_t)0);
}

uint64_t mult_all(const vector<uint64_t>& nums) {
    return accumulate(nums.begin(), nums.end(), (uint64_t)1, multiplies<uint64_t>());
}

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

uint64_t apply_operand(Operand& op, vector<uint64_t> nums){
    switch(op) {
        case Operand::Add:
            return add_all(nums);
        case Operand::Multiply:
            return mult_all(nums);
    }
}

tuple< vector<vector<uint64_t>>, vector<Operand> > parse_input(vector<string> lines)
{
    vector<vector<uint64_t>> numbers{};
    vector<Operand> operands{};

    // collect all number
    int idx = 0;
    for(auto& line: lines)
    {
        istringstream iss(line);
        uint64_t num;
        char ch;
        
        if (idx < lines.size()-1)
        {
            // collect numbers
            numbers.emplace_back();
            while(iss >> num) {
                numbers[idx].push_back(num);
            }
        } else {
            //collect operands
            while(iss >> ch) {
                if(ch == '*'){
                    operands.emplace_back(Operand::Multiply);
                } else if (ch == '+') {
                    operands.emplace_back(Operand::Add);
                }
            }
        }

        ++idx;
    }

    return make_tuple(numbers, operands);
}

vector<vector<uint64_t>> transpose(const vector<vector<uint64_t>>& nums) {
    size_t R = nums.size();
    size_t C = nums[0].size();

    vector<vector<uint64_t>> trans(C, vector<uint64_t>(R));

    for (auto i = 0; i < R; ++i) {
        for (auto j = 0; j < C; ++j) {
            trans[j][i] = nums[i][j];
        }
    }

    return trans;
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

    auto [numbers, ops] = parse_input(lines);

    auto transposed = transpose(numbers);

    uint64_t total = 0;
    int idx = 0;
    for(const auto& nums: transposed) {
        total += apply_operand(ops[idx], nums);
        idx++;
    }

    cout << "Total: " << total << endl;

    return 0;
}