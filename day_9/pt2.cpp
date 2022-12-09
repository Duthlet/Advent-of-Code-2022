#include <iostream>
#include <string>
#include <set>
#include <array>

struct pos {
    int x;
    int y;
};

std::array<pos, 10> rope {};

std::set<pos> visited {};

bool operator< (const pos a, const pos b) {
    if (a.x < b.x) return true;
    if ((a.x == b.x) && (a.y < b.y)) return true;
    return false;
}

void update_rope(int i) {
    if (rope[i].x == rope[i+1].x + 2) {
        ++rope[i+1].x;
        if (rope[i].y < rope[i+1].y) {
            --rope[i+1].y;
        } else {
            rope[i+1].y += (rope[i].y > rope[i+1].y);
        }
    } else if (rope[i].x == rope[i+1].x - 2) {
        --rope[i+1].x;
        if (rope[i].y < rope[i+1].y) {
            --rope[i+1].y;
        } else {
            rope[i+1].y += (rope[i].y > rope[i+1].y);
        }
    } else if (rope[i].y == rope[i+1].y - 2) {
        --rope[i+1].y;
        if (rope[i].x < rope[i+1].x) {
            --rope[i+1].x;
        } else {
            rope[i+1].x += (rope[i].x > rope[i+1].x);
        }
    } else if (rope[i].y == rope[i+1].y + 2) {
        ++rope[i+1].y;
        if (rope[i].x < rope[i+1].x) {
            --rope[i+1].x;
        } else {
            rope[i+1].x += (rope[i].x > rope[i+1].x);
        }
    }
}

void move (std::string &line) {
    for (int n = stoi(line.substr(2,std::string::npos)); n > 0; --n) {
    switch (line[0]) {
        case 'L':
            --rope[0].x;
            if (rope[0].x != rope[1].x - 2) break;
            --rope[1].x;
            rope[1].y = rope[0].y;
            break;
        case 'R':
            ++rope[0].x;
            if (rope[0].x != rope[1].x + 2) break;
            ++rope[1].x;
            rope[1].y = rope[0].y;
            break;
        case 'U':
            ++rope[0].y;
            if (rope[0].y != rope[1].y + 2) break;
            ++rope[1].y;
            rope[1].x = rope[0].x;
            break;
        case 'D':
            --rope[0].y;
            if (rope[0].y != rope[1].y - 2) break;
            --rope[1].y;
            rope[1].x = rope[0].x;
            break;
    };
    for (int i = 1; i < 9; ++i)
        update_rope(i);
    visited.insert(rope[9]);
    }
}

int main () {
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) break;

        move(line);
    }

    std::cout << visited.size() << "\n";
}
