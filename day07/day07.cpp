#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <ranges>
#include <utility>
#include <vector>

int part1(const std::vector<std::set<int>>& rows) {
    int total = 0;
    std::set<int> previous_beams { rows[0] };
    std::set<int> next_beams {};
    for (int i = 1; i < rows.size(); ++i) {
        for (int beam : previous_beams) {
            if (rows[i].contains(beam)) {
                total++;
                next_beams.insert(beam - 1);
                next_beams.insert(beam + 1);
            } else {
                next_beams.insert(beam);
            }
        }
        std::swap(previous_beams, next_beams);
        next_beams.clear();
    }
    return total;
}

long long part2(const std::vector<std::set<int>>& rows) {
    std::map<int, long long> previous_beams { { *rows[0].begin(), 1ll } };
    std::map<int, long long> next_beams {};
    for (int i = 1; i < rows.size(); ++i) {
        for (auto [beam, worlds] : previous_beams) {
            if (rows[i].contains(beam)) {
                next_beams[beam - 1] += worlds;
                next_beams[beam + 1] += worlds;
            } else {
                next_beams[beam] += worlds;
            }
        }
        std::swap(previous_beams, next_beams);
        next_beams.clear();
    }
    return std::accumulate(
        previous_beams.begin(), previous_beams.end(), 0ll,
        [](long long sum, auto entry) { return sum + entry.second; });
}

int main() {
    std::ifstream puzzle_input("day-7-puzzle-input.txt");
    std::string line;

    std::vector<std::set<int>> rows;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::set<int> row;
                auto range = std::ranges::iota_view((std::size_t)0, line.size() - 1);
                std::copy_if(
                    range.begin(), range.end(), std::inserter(row, row.begin()),
                    [&](auto index) { return line[index] != '.'; });
                rows.push_back(row);
            }
        }
    }

    std::cout << part1(rows) << "\n";
    std::cout << part2(rows) << "\n";
}
