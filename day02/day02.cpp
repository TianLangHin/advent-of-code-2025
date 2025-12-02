#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

int digits(long long number) {
    int length = 0;
    while (number) {
        number /= 10;
        length++;
    }
    return length;
}

long long get_power(int length) {
    long long number = 1;
    for (int i = 0; i < length; i++) {
        number *= 10;
    }
    return number;
}

long long get_factor(int length) {
    return get_power(length / 2) + 1;
}

long long part1(const std::vector<std::pair<long long, long long>>& intervals) {
    long long total = 0;
    for (const auto& [fst, snd] : intervals) {
        int digits_lower_bound = digits(fst);
        int digits_upper_bound = digits(snd);
        std::set<long long> factors;
        int lower_threshold = digits_lower_bound - (digits_lower_bound % 2);
        int upper_threshold = digits_upper_bound - (digits_upper_bound % 2);
        factors.insert(get_factor(lower_threshold));
        factors.insert(get_factor(upper_threshold));
        for (long long num = fst; num <= snd; num++) {
            for (auto factor : factors) {
                if (num % factor == 0 && num / factor < factor - 1) {
                    total += num;
                }
            }
        }
    }
    return total;
}

int main() {
    std::ifstream puzzle_input("day-2-puzzle-input.txt");
    // std::ifstream puzzle_input("test-puzzle-input.txt");
    std::string line;

    if (puzzle_input.is_open()) {
        if (puzzle_input.good()) {
            std::getline(puzzle_input, line);
        }
    }

    std::vector<std::pair<long long, long long>> intervals;

    std::stringstream ss;
    ss << line << ',';
    std::string fst, snd;

    std::getline(ss, fst, '-');
    while (!fst.empty()) {
        std::getline(ss, snd, ',');
        intervals.push_back({ std::stoll(fst), std::stoll(snd) });
        std::getline(ss, fst, '-');
    }

    std::cout << part1(intervals) << "\n";
}
