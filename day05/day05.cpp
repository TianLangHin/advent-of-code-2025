#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

typedef long long longlong_t;

longlong_t part1(
    const std::vector<std::pair<longlong_t, longlong_t>>& intervals,
    const std::vector<longlong_t>& ingredients) {

    return std::count_if(ingredients.begin(), ingredients.end(), [&](auto ingredient) {
        return std::find_if(intervals.begin(), intervals.end(), [&](auto interval) {
            return interval.first <= ingredient && ingredient <= interval.second;
        }) != intervals.end();
    });
}

int main() {
    std::fstream puzzle_input("day-5-puzzle-input.txt");
    std::string line;
    bool intervals_done = false;

    std::vector<std::pair<longlong_t, longlong_t>> intervals;
    std::vector<longlong_t> ingredients;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (line.empty()) {
                if (intervals_done) {
                    break;
                } else {
                    intervals_done = true;
                    continue;
                }
            }
            if (!intervals_done) {
                std::stringstream ss;
                std::string component;
                ss << line << '-';
                std::getline(ss, component, '-');
                longlong_t fst = std::stoll(component);
                std::getline(ss, component, '-');
                longlong_t snd = std::stoll(component);
                intervals.push_back({ fst, snd });
            } else {
                ingredients.push_back(std::stoll(line));
            }
        }
    }

    std::cout << part1(intervals, ingredients) << "\n";
}
