#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

typedef std::pair<long long, long long> point_t;

long long rect_area(point_t p1, point_t p2) {
    return std::abs(p1.first - p2.first + 1) * std::abs(p1.second - p2.second + 1);
}

long long part1(const std::vector<point_t> points) {
    long long rectangle = 0;
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            rectangle = std::max(rectangle, rect_area(points[i], points[j]));
        }
    }
    return rectangle;
}

int main() {
    std::ifstream puzzle_input("day-9-puzzle-input.txt");
    std::string line;

    std::vector<point_t> points;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::stringstream ss;
                ss << line << ',';
                std::getline(ss, line, ',');
                int x = std::stoll(line);
                std::getline(ss, line, ',');
                int y = std::stoll(line);
                points.push_back({ x, y });
            }
        }
    }

    std::cout << part1(points) << "\n";
}
