#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

int main() {
    std::string day_number;
    std::cout << "Enter the day number (e.g., 1, 2, ...): ";
    std::cin >> day_number;

    // Validate input
    if (day_number.empty() || !std::all_of(day_number.begin(), day_number.end(), ::isdigit)) {
        std::cerr << "Invalid day number." << std::endl;
        return 1;
    }

    // Create directory for the day
    fs::path day_dir = fs::path("../day" + day_number);
    fs::create_directories(day_dir);

    // Copy template files to day_dir
    fs::path template_dir = "../template";
    for (const auto& entry : fs::directory_iterator(template_dir)) {
        //replace "X" in filenames with the day number
        std::string filename = entry.path().filename().string();
        size_t pos = filename.find("X");
        if (pos != std::string::npos) {
            filename.replace(pos, 1, day_number);
        }
        fs::path dest = day_dir / filename;
        fs::copy_file(entry.path(), dest, fs::copy_options::overwrite_existing);

        //fs::path dest = day_dir / entry.path().filename();
        //fs::copy_file(entry.path(), dest, fs::copy_options::overwrite_existing);
    }

    std::cout << "Created files for Day " << day_number << " in " << day_dir << std::endl;

    return 0;
}