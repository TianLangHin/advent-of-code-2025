#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::unordered_set<std::string> visited_t;
typedef std::unordered_map<std::string, std::vector<std::string>> graph_t;

int dfs_count(const std::string device, const graph_t& server_rack, visited_t& visited) {
    if (device == "out") {
        return 1;
    }
    if (visited.contains(device)) {
        return 0;
    }
    int total = 0;
    for (std::string next_device : server_rack.at(device)) {
        visited.insert(device);
        total += dfs_count(next_device, server_rack, visited);
        visited.erase(device);
    }
    return total;
}

int part1(const graph_t& server_rack) {
    visited_t visited;
    return dfs_count("you", server_rack, visited);
}

int main() {
    std::ifstream puzzle_input("day-11-puzzle-input.txt");
    std::string line;

    graph_t server_rack;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                std::stringstream ss;
                ss << line << ' ';
                std::string input_device, device;
                std::getline(ss, input_device, ':');
                std::getline(ss, device, ' ');
                std::getline(ss, device, ' ');
                while (!device.empty()) {
                    server_rack[input_device].push_back(device);
                    std::getline(ss, device, ' ');
                }
            }
        }
    }

    std::cout << part1(server_rack) << "\n";
}
