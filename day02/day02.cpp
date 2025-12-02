#include <fstream>
#include <iostream>
#include <numeric>
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

std::pair<long long, long long> get_factor_and_threshold(int length, int order) {
    long long value = 1;
    long long multiple = get_power(length / order);
    for (int i = 0; i < order - 1; i++) {
        value = value * multiple + 1;
    }
    return { value, multiple };
}

int lowest_multiple_of(int numerator, int denominator) {
    return numerator - numerator % denominator;
}

long long part1(const std::vector<std::pair<long long, long long>>& intervals) {
    long long total = 0;
    for (const auto& [fst, snd] : intervals) {
        int digits_lower_bound = digits(fst);
        int digits_upper_bound = digits(snd);

        std::set<std::pair<long long, long long>> factors;
        int lower_threshold = lowest_multiple_of(digits_lower_bound, 2);
        int upper_threshold = lowest_multiple_of(digits_upper_bound, 2);
        factors.insert(get_factor_and_threshold(lower_threshold, 2));
        factors.insert(get_factor_and_threshold(upper_threshold, 2));

        for (long long num = fst; num <= snd; num++) {
            for (auto& [factor, threshold] : factors) {
                if (num % factor == 0 && num / factor < threshold) {
                    total += num;
                }
            }
        }
    }
    return total;
}

long long part2(const std::vector<std::pair<long long, long long>>& intervals) {
    std::set<long long> invalid_ids;
    for (const auto& [fst, snd] : intervals) {
        int digits_lower_bound = digits(fst);
        int digits_upper_bound = digits(snd);

        std::set<std::pair<long long, long long>> factors;
        for (int order = 2; order < 20; order++) {
            int lower_threshold = lowest_multiple_of(digits_lower_bound, order);
            int upper_threshold = lowest_multiple_of(digits_upper_bound, order);
            factors.insert(get_factor_and_threshold(lower_threshold, order));
            factors.insert(get_factor_and_threshold(upper_threshold, order));
        }

        for (long long num = fst; num <= snd; num++) {
            for (auto& [factor, threshold] : factors) {
                if (num % factor == 0 && num / factor < threshold) {
                    invalid_ids.insert(num);
                }
            }
        }
    }
    return std::reduce(invalid_ids.begin(), invalid_ids.end());
}

int main() {
    std::ifstream puzzle_input("day-2-puzzle-input.txt");
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
    std::cout << part2(intervals) << "\n";
}
