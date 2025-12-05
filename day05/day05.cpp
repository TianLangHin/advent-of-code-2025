#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

typedef long long longlong_t;
typedef std::pair<longlong_t, longlong_t> interval_t;

longlong_t part1(
    const std::vector<interval_t>& intervals,
    const std::vector<longlong_t>& ingredients) {

    return std::count_if(ingredients.begin(), ingredients.end(), [&](auto ingredient) {
        return std::find_if(intervals.begin(), intervals.end(), [&](auto interval) {
            return interval.first <= ingredient && ingredient <= interval.second;
        }) != intervals.end();
    });
}

int find_left(interval_t new_interval, const std::vector<interval_t>& intervals) {
    int left = 0, right = intervals.size();
    while (left < right) {
        int middle = (left + right) >> 1;
        if (new_interval.first < intervals[middle].first) {
            right = middle;
        } else if (new_interval.first > intervals[middle].second) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return left;
}

int find_right(interval_t new_interval, const std::vector<interval_t>& intervals) {
    int left = 0, right = intervals.size();
    while (left < right) {
        int middle = (left + right) >> 1;
        if (new_interval.second < intervals[middle].first) {
            right = middle;
        } else if (new_interval.second > intervals[middle].second) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return right - 1;
}

longlong_t part2(const std::vector<interval_t>& intervals) {
    std::vector<interval_t> interval_list;
    for (auto interval : intervals) {
        int leftmost_merge = find_left(interval, interval_list);
        int rightmost_merge = find_right(interval, interval_list);

        auto begin_it = interval_list.begin();
        if (leftmost_merge > rightmost_merge) {
            interval_list.insert(begin_it + leftmost_merge, interval);
        } else {
            interval_t overlapped_interval {
                std::min(interval.first, interval_list[leftmost_merge].first),
                std::max(interval.second, interval_list[rightmost_merge].second)
            };
            interval_list.erase(begin_it + leftmost_merge, begin_it + rightmost_merge + 1);
            interval_list.insert(begin_it + leftmost_merge, overlapped_interval);
        }
    }
    return std::accumulate(interval_list.begin(), interval_list.end(), 0ll, [](auto sum, auto interval) {
        return sum + interval.second - interval.first + 1;
    });
}

int main() {
    std::fstream puzzle_input("day-5-puzzle-input.txt");
    // std::fstream puzzle_input("test-puzzle-input.txt");
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
    std::cout << part2(intervals) << "\n";
}
