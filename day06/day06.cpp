#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <sstream>
#include <vector>

long long part1(
    const std::vector<std::vector<long long>> numbers,
    const std::vector<bool> is_adding) {

    auto col_indices = std::ranges::iota_view((std::size_t)0, numbers[0].size());
    auto row_indices = std::ranges::iota_view((std::size_t)0, numbers.size());
    return std::accumulate(col_indices.begin(), col_indices.end(), 0ll, [&](auto sum, auto col) {
        return sum + std::accumulate(
            row_indices.begin(),
            row_indices.end(),
            is_adding[col] ? 0ll : 1ll,
            [&](auto acc, auto row) {
                return is_adding[col] ? acc + numbers[row][col] : acc * numbers[row][col];
            });
    });
}

int main() {
    std::ifstream puzzle_input("day-6-puzzle-input.txt");
    std::string line;

    std::vector<std::vector<long long>> numbers;
    std::vector<bool> is_adding;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::istringstream iss(line);
                std::vector<std::string> parsed_line {
                    std::istream_iterator<std::string>(iss),
                    std::istream_iterator<std::string>()
                };
                if (line[0] == '+' || line[0] == '*') {
                    std::transform(
                        parsed_line.begin(),
                        parsed_line.end(),
                        std::back_inserter(is_adding),
                        [](std::string n) { return n == "+"; });
                } else {
                    std::vector<long long> row;
                    std::transform(
                        parsed_line.begin(),
                        parsed_line.end(),
                        std::back_inserter(row),
                        [](std::string n) { return std::stoi(n); });
                    numbers.push_back(row);
                }
            }
        }
    }

    std::cout << part1(numbers, is_adding) << "\n";
}
