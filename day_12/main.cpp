#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <climits>

std::vector<std::string> map;
std::vector<std::vector<int>> min;

int sy, sx, ey, ex;

void read_input() {
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) {
            break;
        }

        int i = line.find('S');
        if (i != std::string::npos) {
            sy = map.size();
            sx = i;
            line[i] = 'a';
            std::cout << "Start is at (" << sx << ", " << sy << ")\n";
        }
        i = line.find('E');
        if (i != std::string::npos) {
            ey = map.size();
            ex = i;
            line[i] = 'z';
            std::cout << "End is at (" << ex << ", " << ey << ")\n";
        }

        map.push_back(line);
        min.emplace_back(line.length(), INT_MAX);
    }
}

void print_map() {
    for (auto &s : map) std::cout << s << "\n";
}

void print_min() {
    for (auto &v : min) {
        for (auto i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

bool in_bounds (int x, int y) {
    return !((x < 0) || (y < 0) || (x >= map[0].length()) || (y >= map.size()));
}

int part1() {
    int x, y, x2, y2;
    std::queue<std::pair<int, int>> q {};
    min[sy][sx] = 0;
    q.push({sx, sy});

    auto update2 = [&]() {
        if ((in_bounds(x2, y2) && ( map[y][x] - map [y2][x2] ) >= -1)) {
            if (min[y2][x2] > min[y][x] + 1) {
                min[y2][x2] = min[y][x] + 1;
                q.push({x2, y2});
            }
        }
    };

    while (!q.empty()) {
        auto pos = q.front();
        q.pop();

        x = pos.first;
        y = pos.second;

        x2 = x-1;
        y2 = y;
        update2();
        x2 = x+1;
        update2();
        x2 = x;
        y2 = y-1;
        update2();
        y2 = y+1;
        update2();
    }
    return min[ey][ex];
}

int part2 () {
    int _min = INT_MAX;
    for (int y = 0; y < map.size(); ++y) for (int x = 0; x < map[y].length(); ++x) if (map[y][x] == 'a') {
        //init min
        for (auto &v : min) for (auto &i : v) i = INT_MAX;
        sx = x;
        sy = y;
        part1();
        if (_min > min[ey][ex]) _min = min[ey][ex];
    }
    return _min;
}

int main () {
    read_input();
    std::cout << "Solution of part 1: " << part1() << "\n";
    std::cout << "Solution of part 2: " << part2() << "\n";
}
