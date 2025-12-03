#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int part1(const std::vector<std::vector<int>>& batteries) {
    int total = 0;
    for (const std::vector<int>& row : batteries) {
        auto it1 = std::max_element(row.begin(), row.end() - 1);
        auto it2 = std::max_element(it1 + 1, row.end());
        total += 10 * (*it1) + (*it2);
    }
    return total;
}

long long part2(const std::vector<std::vector<int>>& batteries) {
    long long total = 0;
    for (const std::vector<int>& row : batteries) {
        long long number = 0;
        int start_index = 0;
        for (int remaining = 11; remaining >= 0; remaining--) {
            auto it = std::max_element(row.begin() + start_index, row.end() - remaining);
            start_index = it - row.begin() + 1;
            number = number * 10 + *it;
        }
        total += number;
    }
    return total;
}

int main() {
    std::ifstream puzzle_input("day-3-puzzle-input.txt");
    std::string line;

    std::vector<std::vector<int>> batteries;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);

            std::vector<int> battery_line;
            for (char c : line) {
                int digit = (int)(c - '0');
                battery_line.push_back(digit);
            }
            if (!battery_line.empty()) {
                batteries.push_back(battery_line);
            }
        }
    }

    std::cout << part1(batteries) << "\n";
    std::cout << part2(batteries) << "\n";
}
