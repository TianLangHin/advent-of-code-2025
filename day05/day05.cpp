#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

typedef std::pair<long long, long long> interval_t;

// Brute force solution for Part 1.
long long part1(
    const std::vector<interval_t>& intervals,
    const std::vector<long long>& ingredients) {

    return std::count_if(ingredients.begin(), ingredients.end(), [&](auto ingredient) {
        return std::find_if(intervals.begin(), intervals.end(), [&](auto interval) {
            return interval.first <= ingredient && ingredient <= interval.second;
        }) != intervals.end();
    });
}

// If `from_left` is true, returns a value `i` in `[0, n]`
// such that all `intervals[j]` for `j in [0, i)` do not overlap with `new_interval`.
// If `from_right` is true, returns a value `i` in `[-1, n-1]`
// such that all `intervals[j]` for `j in (i, n-1]` do not overlap with `new_interval`.
int find_boundary(
    interval_t new_interval,
    const std::vector<interval_t>& intervals,
    bool from_left) {

    // To test whether the `intervals[middle]` could overlap with `interval`,
    // we use only one end of the `interval`.
    auto target = from_left ? new_interval.first : new_interval.second;

    // Assumes that `intervals` contains non-overlapping intervals in ascending order.
    // Utilises binary search since an ordering exists.
    // `left` is inclusive while `right` is exclusive.
    int left = 0, right = intervals.size();

    while (left < right) {
        int middle = (left + right) >> 1;
        if (target < intervals[middle].first) {
            // In this case, `intervals[middle]` cannot contain `target`,
            // and by the ordering of `intervals`, neither can `intervals[j]`
            // for all `j >= middle`.
            right = middle;
        } else if (target > intervals[middle].second) {
            // In this case, `intervals[middle]` cannot contain `target`,
            // and by the ordering of `intervals`, neither can `intervals[j]`
            // for all `j <= middle`.
            left = middle + 1;
        } else {
            // In this binary search,
            // the notion of a "match" is the relavant bound of our `interval`
            // is contained within any of the elements of `intervals`.
            return middle;
        }
    }
    // However, there may be no elements in `intervals` that overlap with `interval`.
    // In this form, the search always returns the index of the smallest element
    // such that `target` is less than that interval's lower bound.
    // If `from_left` is true, all intervals up to (but not including) this index
    // exclude `target` and are lesser.
    // If `from_left` is false, all intervals from this index and above (including this index)
    // exclude the `target` and are greater.
    // Hence, in this case, we subtract one to return an exclusive lower bound.
    return from_left ? left : right - 1;
}

long long part2(const std::vector<interval_t>& intervals) {
    std::vector<interval_t> interval_list;
    for (auto interval : intervals) {
        // From these, we find that all `intervals[j]` for `j in [0, left)` or `j in (right, n-1]`
        // cannot overlap with `interval`.
        // Thus, all `intervals[i]` for `i in [left, right]` must be removed
        // before the new interval created by unioning `interval` with all `interval[i]`
        // is inserted into `interval_list`.
        int left = find_boundary(interval, interval_list, true);
        int right = find_boundary(interval, interval_list, false);

        auto begin_it = interval_list.begin();
        if (left > right) {
            // In this case, `[left, right]` is an empty set,
            // meaning `interval` overlaps with no existing elements.
            interval_list.insert(begin_it + left, interval);
        } else {
            interval_t overlapped_interval {
                std::min(interval.first, interval_list[left].first),
                std::max(interval.second, interval_list[right].second)
            };
            interval_list.erase(begin_it + left, begin_it + right + 1);
            interval_list.insert(begin_it + left, overlapped_interval);
        }
    }
    // Finally, we add up the size of all intervals `[a_i, b_i]` which is `b_i - a_i + 1`.
    return std::accumulate(interval_list.begin(), interval_list.end(), 0ll, [](auto sum, auto interval) {
        return sum + interval.second - interval.first + 1;
    });
}

int main() {
    std::fstream puzzle_input("day-5-puzzle-input.txt");
    std::string line;
    bool intervals_done = false;

    std::vector<interval_t> intervals;
    std::vector<long long> ingredients;

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
                long long fst = std::stoll(component);
                std::getline(ss, component, '-');
                long long snd = std::stoll(component);
                intervals.push_back({ fst, snd });
            } else {
                ingredients.push_back(std::stoll(line));
            }
        }
    }

    std::cout << part1(intervals, ingredients) << "\n";
    std::cout << part2(intervals) << "\n";
}
