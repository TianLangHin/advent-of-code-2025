#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<std::vector<bool>> grid_t;
typedef std::vector<std::pair<int, int>> points_t;

std::array<std::pair<int, int>, 8> offsets {
    std::pair { 1, 1 },
    std::pair { 1, 0 },
    std::pair { 1, -1 },
    std::pair { 0, -1 },
    std::pair { -1, -1 },
    std::pair { -1, 0 },
    std::pair { -1, 1 },
    std::pair { 0, 1 }
};

int is_accessible(int x, int y, const grid_t& grid) {
    int x_lim = grid[0].size();
    int y_lim = grid.size();
    if (x < 0 || x >= x_lim) {
        return 0;
    }
    if (y < 0 || y >= y_lim) {
        return 0;
    }
    return grid[y][x] ? 1 : 0;
}

points_t all_accessible(const grid_t& grid) {
    points_t points;
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            if (grid[row][col]) {
                int subtotal = 0;
                for (auto& [x_offset, y_offset] : offsets) {
                    subtotal += is_accessible(col + x_offset, row + y_offset, grid);
                }
                if (subtotal < 4) {
                    points.push_back({ row, col });
                }
            }
        }
    }
    return points;
}

void remove_with(grid_t& grid, const points_t& points) {
    for (auto [row, col] : points) {
        grid[row][col] = false;
    }
}

int part1(const grid_t& grid) {
    return all_accessible(grid).size();
}

int part2(grid_t& grid) {
    int total = 0;
    points_t points_to_remove = all_accessible(grid);
    while (points_to_remove.size() != 0) {
        total += points_to_remove.size();
        remove_with(grid, points_to_remove);
        points_to_remove = all_accessible(grid);
    }
    return total;
}

int main() {
    std::ifstream puzzle_input("day-4-puzzle-input.txt");
    std::vector<std::vector<bool>> grid;
    std::string line;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::vector<bool> row;
                std::transform(line.begin(), line.end(), std::back_inserter(row), [](char c) {
                    return c == '@';
                });
                grid.push_back(row);
            }
        }
    }

    std::cout << part1(grid) << "\n";
    std::cout << part2(grid) << "\n";
}
