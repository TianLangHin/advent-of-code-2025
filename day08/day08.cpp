#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

typedef std::tuple<int, int, int> point_t;
typedef std::tuple<long long, point_t, point_t> connection_t;
typedef std::map<point_t, std::vector<point_t>> graph_t;

long long squared_dist(point_t p1, point_t p2) {
    auto [x1, y1, z1] = p1;
    auto [x2, y2, z2] = p2;
    long long x = x2 - x1, y = y2 - y1, z = z2 - z1;
    return x*x + y*y + z*z;
}

bool comparator(connection_t c1, connection_t c2) {
    return std::get<0>(c1) < std::get<0>(c2);
}

int dfs(point_t point, const graph_t& graph, std::set<point_t>& seen) {
    if (seen.contains(point)) {
        return 0;
    }
    seen.insert(point);
    int total = 1;
    for (auto next_point : graph.at(point)) {
        total += dfs(next_point, graph, seen);
    }
    return total;
}

int part1(const std::vector<point_t>& points) {
    int pair_number = 1000;
    std::vector<connection_t> connections {};
    for (int i = 0; i < points.size(); ++i) {
        point_t p1 = points[i];
        for (int j = i+1; j < points.size(); ++j) {
            point_t p2 = points[j];
            if (p1 == p2) {
                continue;
            }
            connections.push_back({ squared_dist(p1, p2), p1, p2 });
            std::push_heap(connections.begin(), connections.end(), comparator);
            if (connections.size() > pair_number) {
                std::pop_heap(connections.begin(), connections.end(), comparator);
                connections.pop_back();
            }
        }
    }
    graph_t graph;
    for (auto [_, p1, p2] : connections) {
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }
    std::vector<int> cluster_sizes;
    std::set<point_t> seen;
    for (auto [point, _] : graph) {
        int cluster_size = dfs(point, graph, seen);
        if (cluster_size == 0) {
            continue;
        }
        cluster_sizes.push_back(cluster_size);
        std::push_heap(cluster_sizes.begin(), cluster_sizes.end(), std::greater<int> {});
        if (cluster_sizes.size() > 3) {
            std::pop_heap(cluster_sizes.begin(), cluster_sizes.end(), std::greater<int> {});
            cluster_sizes.pop_back();
        }
    }
    return std::accumulate(cluster_sizes.begin(), cluster_sizes.end(), 1, std::multiplies<int> {});
}

int main() {
    std::ifstream puzzle_input("day-8-puzzle-input.txt");
    // std::ifstream puzzle_input("test-puzzle-input.txt");
    std::string line;

    std::vector<point_t> points;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::stringstream ss;
                ss << line << ',';
                std::getline(ss, line, ',');
                int x = std::stoi(line);
                std::getline(ss, line, ',');
                int y = std::stoi(line);
                std::getline(ss, line, ',');
                int z = std::stoi(line);
                points.push_back({ x, y, z });
            }
        }
    }

    std::cout << part1(points) << "\n";
}
