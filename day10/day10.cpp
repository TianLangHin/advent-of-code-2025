#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

typedef std::tuple<int, std::vector<int>, std::vector<int>> machine_t;

long long part1(const std::vector<machine_t>& machines) {
    long long total = 0;
    for (auto machine : machines) {
        auto [target, buttons, joltages] = machine;
        std::deque<std::pair<int, long long>> frontier { { 0, 0ll } };
        while (!frontier.empty()) {
            auto [presses, mask] = frontier.front();
            frontier.pop_front();
            if (mask == target) {
                total += presses;
                break;
            }
            presses++;
            for (int button : buttons) {
                frontier.push_back({ presses, mask ^ button });
            }
        }
    }
    return total;
}

int main() {
    std::ifstream puzzle_input("day-10-puzzle-input.txt");
    std::string line;

    std::vector<machine_t> machines;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                int target_mask = 0;
                std::vector<int> buttons;
                std::vector<int> joltages;

                std::stringstream ss;
                ss << line << ' ' << ' ';
                std::getline(ss, line, ' ');
                while (!line.empty()) {
                    if (line[0] == '[') {
                        for (int i = 1; i < line.size() - 1; ++i) {
                            if (line[i] == '#') {
                                target_mask |= 1 << (i - 1);
                            }
                        }
                    } else if (line[0] == '(') {
                        int button_mask = 0;
                        std::stringstream number_ss;
                        number_ss << line.substr(1, line.size() - 2) << ',';
                        std::getline(number_ss, line, ',');
                        while (!line.empty()) {
                            int position = std::stoi(line);
                            button_mask |= 1 << position;
                         std::getline(number_ss, line, ',');
                        }
                        buttons.push_back(button_mask);
                    } else if (line[0] == '{') {
                        std::stringstream number_ss;
                        number_ss << line.substr(1, line.size() - 2) << ',';
                        std::getline(number_ss, line, ',');
                        while (!line.empty()) {
                            int joltage = std::stoi(line);
                            joltages.push_back(joltage);
                            std::getline(number_ss, line, ',');
                        }
                    }
                    std::getline(ss, line, ' ');
                }
                machines.push_back({ target_mask, buttons, joltages });
            }
        }
    }

    std::cout << part1(machines) << "\n";
}
