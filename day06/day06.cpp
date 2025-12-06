#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

typedef std::pair<std::vector<std::vector<long long>>, std::vector<bool>> part1_t;

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

part1_t part1_parse(std::string filename) {
    std::ifstream puzzle_input(filename);
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

    return { numbers, is_adding };
}

long long part2(std::vector<std::string> lines) {
    std::string operators = lines.back();

    long long total = 0;
    std::vector<long long> numbers;
    int previous_operator = 0;

    for (int col = 0; col < operators.size(); col++) {
        if (operators[col] != ' ' && previous_operator != col) {
            char op = operators[previous_operator];
            long long result = op == '+'
                ? std::accumulate(numbers.begin(), numbers.end(), 0ll, std::plus<long long> {})
                : std::accumulate(numbers.begin(), numbers.end(), 1ll, std::multiplies<long long> {});
            total += result;
            numbers.clear();
            previous_operator = col;
        }
        long long number = 0ll;
        bool non_empty = false;
        for (int row = 0; row < lines.size() - 1; row++) {
            if (lines[row][col] == ' ') {
                continue;
            }
            non_empty = true;
            number = number * 10 + (long long)(lines[row][col] - '0');
        }
        if (non_empty) {
            numbers.push_back(number);
        }
    }
    char op = operators[previous_operator];
    long long result = op == '+'
        ? std::accumulate(numbers.begin(), numbers.end(), 0ll, std::plus<long long> {})
        : std::accumulate(numbers.begin(), numbers.end(), 1ll, std::multiplies<long long> {});
    total += result;
    return total;
}

int main() {
    std::string filename = "day-6-puzzle-input.txt";

    auto [numbers, is_adding] = part1_parse(filename);
    std::cout << part1(numbers, is_adding) << "\n";

    std::ifstream puzzle_input(filename);
    std::vector<std::string> lines;
    std::string line;
    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
    }

    std::cout << part2(lines) << "\n";
}
