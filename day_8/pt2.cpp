#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> map{};

int view_score (int x, int y) {
    int value = map[y][x];
    int score = 1;
    int mult;

    mult = 0;
    for (int y2 = y-1; y2 >= 0; --y2) {
        ++mult;
        if (map[y2][x] >= value) break;
    }
    score *= mult;
    mult = 0;
    for (int y2 = y+1; y2 < map.size(); ++y2) {
        ++mult;
        if (map[y2][x] >= value) break;
    }
    score *= mult;
    mult = 0;
    for (int x2 = x-1; x2 >= 0; --x2) {
        ++mult;
        if (map[y][x2] >= value) break;
    }
    score *= mult;
    mult = 0;
    for (int x2 = x+1; x2 < map[0].length(); ++x2) {
        ++mult;
        if (map[y][x2] >= value) break;
    }
    score *= mult;

    return score;
}

int main () {
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) break;

        map.push_back(line);
    }
    int pt2 = 0;
    for (int x = 0; x < map[0].length(); ++x) {
        for (int y = 0; y < map.size(); ++y) {
            pt2 = std::max(view_score(x,y), pt2);
        }
    }

    std::cout << pt2 << "\n";
}
