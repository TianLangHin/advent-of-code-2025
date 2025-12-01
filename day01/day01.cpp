#include <fstream>
#include <iostream>
#include <vector>

void part1(std::vector<std::string>& dials) {
    int password = 0;
    int dial_number = 50;
    for (std::string rotation : dials) {
        int movement = std::stoi(rotation.substr(1));
        if (rotation[0] == 'L') {
            dial_number = (100 + dial_number - movement) % 100;
        } else if (rotation[0] == 'R') {
            dial_number = (dial_number + movement) % 100;
        }
        if (dial_number == 0) {
            password++;
        }
    }
    std::cout << password << "\n";
}

int rotations(int start, int movement, int span) {
    int clicks = 0;
    int dial = start;
    if (movement >= 0) {
        for (int i = 0; i < movement; i++) {
            dial = (dial + 1) % span;
            if (dial == 0) {
                clicks++;
            }
        }
    } else {
        for (int i = 0; i < -movement; i++) {
            dial = (dial + 99) % span;
            if (dial == 0) {
                clicks++;
            }
        }
    }
    return clicks;
}

void part2(std::vector<std::string>& dials) {
    int password = 0;
    int dial_number = 50;
    for (std::string rotation : dials) {
        int movement = std::stoi(rotation.substr(1));
        int crosses = 0;
        if (rotation[0] == 'L') {
            crosses = rotations(dial_number, -movement, 100);
            dial_number = (100 + dial_number - movement) % 100;
        } else if (rotation[0] == 'R') {
            crosses = rotations(dial_number, movement, 100);
            dial_number = (dial_number + movement) % 100;
        }
        password += crosses;
    }
    std::cout << password << "\n";
}

int main() {
    std::ifstream puzzle_input("day-1-puzzle-input.txt");
    std::string line;

    std::vector<std::string> dials;

    if (puzzle_input.is_open()) {
        while (puzzle_input.good()) {
            std::getline(puzzle_input, line);
            if (!line.empty()) {
                dials.push_back(line);
            }
        }
    }

    part1(dials);
    part2(dials);
}
