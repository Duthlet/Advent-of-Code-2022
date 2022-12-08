#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> map{};

void update (char& c, int& highest) {
    char mask = 1<<7;
    char value = (c & ~mask) - '0';
    if (value > highest) {
        c |= mask;
        highest = value;
    }
}

bool check (const char& c) {
    char mask = 1<<7;
    return c & mask;
}

void mark_left_visible () {
    for (auto &s : map) {
        int highest = -1;
        for (auto &c : s) {
            update (c, highest);
        }
    }
}
void mark_top_visible () {
    for (int x = 0; x < map[0].length(); ++x) {
        int highest = -1;
        for (int y = 0; y < map.size(); ++y) {
            update (map[y][x], highest);
        }
    }
}
void mark_right_visible () {
    for (auto &s : map) {
        int highest = -1;
        for (int x = s.length()-1; x >= 0; --x) {
            update (s[x], highest);
        }
    }
}
void mark_bottom_visible () {
    for (int x = 0; x < map[0].length(); ++x) {
        int highest = -1;
        for (int y = map.size()-1; y >= 0; --y) {
            update (map[y][x], highest);
        }
    }
}

int main () {
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) break;

        map.push_back(line);
    }

    mark_left_visible ();
    mark_top_visible ();
    mark_bottom_visible ();
    mark_right_visible ();

    long pt1 = 0;
    for (auto &s : map) {
        for (auto &c : s) {
            pt1 += check (c);
        }
    }

    std::cout << pt1 << "\n";
}
