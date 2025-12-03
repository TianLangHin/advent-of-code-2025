#include <fstream>
#include <iostream>
#include <vector>

int part1(const std::vector<std::vector<int>>& batteries) {
    int total = 0;
    for (const std::vector<int>& row : batteries) {
        std::vector<int> left;
        std::vector<int> right;
        int left_max = 0;
        left.push_back(left_max);
        for (int i = 0; i < row.size() - 1; i++) {
            left_max = std::max(left_max, row[i]);
            left.push_back(left_max);
        }
        int right_max = row.back();
        right.push_back(right_max);
        for (int i = row.size() - 2; i >= 0; i--) {
            right_max = std::max(right_max, row[i]);
            right.push_back(right_max);
        }
        int best = 0;
        for (int i = 0; i < row.size(); i++) {
            best = std::max(best, left[i] * 10 + right[row.size() - 1 - i]);
        }
        total += best;
    }
    return total;
}

int main() {
    std::ifstream puzzle_input("day-3-puzzle-input.txt");
    // std::ifstream puzzle_input("test-puzzle-input.txt");
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
}
