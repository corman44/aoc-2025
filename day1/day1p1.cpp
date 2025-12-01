#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int32_t get_max(vector<int32_t> input)
{
    int32_t max{};
    for (auto& num : input)
    {
        max = abs(num) > max ? abs(num) : max;
    }
    return max;
}

vector<int32_t> parse_input(string input)
{
    vector<int32_t> rots{};
    istringstream stream(input);
    string str{};
    while(getline(stream,str))
    {
        int32_t multiplyer = 1;       // Check for L 
        if (str[0] == 'L')
        {
            multiplyer = -1;
        }

        // convert to digits
        int32_t val = 0;
        for (int i = 1; i<str.size(); ++i)
        {
            if (isdigit(str[i]))
            {
                val *= 10;
                val += str[i] - '0';
            }
        }

        // clip extra rotations and apply multiplyer
        //val = (val % 100) * multiplyer;
        val *= multiplyer;
        rots.push_back(val);
    }

    return rots;
}

int main(int argc, char** argv) {
    std::string path = (argc > 1) ? argv[1] : "input.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open '" << path << "'\n";
        return 2;
    }

    // Using Example input
    string test_input = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";

    // PART 1
    int32_t position = 50;
    int zeros = 0;
    //for (auto& rot: rots)
    //{
        //position += rot;
        //position = position % 100;
        //position = position < 0 ? 100 + position : position;
        //if (position == 0)
        //{
            //zeros++;
        //}
    //}

    //cout << "Num Zeros: " << zeros << "\n";

    //auto rots = parse_input(test_input);

    // Using Real input
    string input{};
    string str{};
    while (getline(in,str))
    {
        input.append(str + '\n');
    }

    auto rots = parse_input(input);

    bool prev_zero = false;
    // PART 2
    for (auto& rot: rots)
    {
        for (int32_t i = 0; i < abs(rot); i++)
        {
            int32_t temp = rot < 0 ? -1 : 1;

            position += temp;

            if (position > 99)
            {
                position = 0;
            }
            else if (position < 0)
            {
                position = 99;
            }
            zeros += position == 0 ? 1 : 0;
        }
    }
    //IGNORE COMMENTS.. it only contains pain...

        //position += rot;

        // handle multiple rotations around 100 (+ and -)
        //if (abs(position) > 100 )
        //{
            //auto tmp = abs(position) / 100;
            //tmp += tmp * 100 == position ? -1 : 0; 
            //zeros += tmp;
        //}

        // handle crossing over zero going negative (if last wasn't 0)
        //if(position < 0 && !prev_zero)
        //{
            //zeros++;
        //}

        // apply mod and flip if negative
        //position = position % 100;
        //position = position < 0 ? 100 + position : position;

        //prev_zero = false;
        //if (position == 0)
        //{
            //zeros++;
            //prev_zero = true;
        //} }

    cout << "Num Zeros: " << zeros << "\n";

    return 0;
}

// Attempts: 2228, 6654, 6595, 6644, 6736, 6634