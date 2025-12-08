#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum Cell {
    Empty,
    Splitter,
    Start,
    Beam,
};

struct Coord {
    int64_t row, col;
    
    bool operator==(const Coord& other) const {
        return row == other.row && col == other.col;
    }
};

namespace std {
    template <>
    struct hash<Coord> {
        size_t operator()(const Coord& c) const {
            return hash<int64_t>{}(c.row) ^ (hash<int64_t>{}(c.col) << 1);
        }
    };
}

vector<vector<Cell>> parse_input(vector<string> lines)
{
    // start location: S
    // . = empy space
    // ^ = beam stopped and split
    vector<vector<Cell>> cells{};
    int i = 0;
    
    for(const auto& line: lines) {
        cells.emplace_back();
        for(const auto& c: line) {
            switch (c) {
                case '.':
                    cells[i].emplace_back(Cell::Empty);
                    break;
                case '^':
                    cells[i].emplace_back(Cell::Splitter);
                    break;
                case 'S':
                    cells[i].emplace_back(Cell::Start);
                    break;
                default:
                    cout << "ERROR: swtich(" << c << ") undefined" << endl;
                    break;
            }
        }
        ++i;
    }
    return cells;
}

bool step_beams(vector<vector<Cell>>& cells, unordered_set<Coord>& beams, uint16_t& splits_hit) {
    bool beams_updated{};
    auto row_size = cells.size();
    auto col_size = cells[0].size();

    vector<Coord> to_remove{};
    Coord l_beam{};

    for (auto& beam: beams) {
        // check if out of range
        if (beam.row >= row_size - 1 || beam.col < 0 || beam.col >= col_size - 1) {
            to_remove.push_back(beam);
            continue;
        }
        // check if next is splitter otherwise move beam down
        else if (cells[beam.row+1][beam.col] == Cell::Splitter) {
            splits_hit++;
            l_beam.row = beam.row + 1;
            l_beam.col = beam.col - 1;
            beams_updated = true;

            //apply beams to cells
            cells[l_beam.row][l_beam.col] = Cell::Beam;
            cells[l_beam.row][l_beam.col + 2] = Cell::Beam;
            //beams.erase(beam);
            to_remove.push_back(beam);
            beams.emplace(l_beam);
            l_beam.col += 2;
            beams.emplace(l_beam);
            
        }
        else {
            l_beam = beam;
            l_beam.row += 1;
            cells[l_beam.row][l_beam.col] = Cell::Beam;
            //beams.erase(beam);
            to_remove.push_back(beam);
            beams.emplace(l_beam);
            beams_updated = true;
        }
    }

    // remove collection of previous beams
    for(auto& beam: to_remove) {
        beams.erase(beam);
    }

    return beams_updated;
}

void print_cells(const vector<vector<Cell>> cells) {
    for (const auto& line: cells) {
        for (const auto& c: line) {
            switch (c)
            {
            case Cell::Beam:
                cout << '|';
                break;
            case Cell::Empty:
                cout << '.';
                break;
            case Cell::Start:
                cout << 'S';
                break;
            case Cell::Splitter:
                cout << '^';
                break;
            }
        }
        cout << endl;
    }
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

    auto cells = parse_input(lines);

    //count splitters
    // 1713 in input
    //int count = 0;
    //for (const auto& line: cells) {
        //for(const auto& c: line) {
            //count += c == Cell::Splitter ? 1 : 0;
        //}
    //}

    uint16_t splits_hit=0;
    bool updated=true;
    const auto& start_col = find(cells[0].begin(), cells[0].end(), Cell::Start) - cells[0].begin();
    unordered_set<Coord> beams{};
    beams.insert(Coord{0, static_cast<int64_t>(start_col)});
    while(updated) {
        updated = step_beams(cells, beams,splits_hit);
    }

    print_cells(cells);

    cout << "Splits Hit: " << splits_hit << endl;

    return 0;
}

// Too High: 3386