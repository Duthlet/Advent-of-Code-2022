#include <iostream>
#include <string>
#include <set>

struct pos {
    int x;
    int y;
};

pos head, tail;

std::set<pos> visited {};

bool operator< (const pos a, const pos b) {
    if (a.x < b.x) return true;
    if ((a.x == b.x) && (a.y < b.y)) return true;
    return false;
}

void move (std::string &line) {
    for (int n = stoi(line.substr(2,std::string::npos)); n > 0; --n) {
    switch (line[0]) {
        case 'L':
            --head.x;
            if (head.x != tail.x - 2) break;
            --tail.x;
            tail.y = head.y;
            break;
        case 'R':
            ++head.x;
            if (head.x != tail.x + 2) break;
            ++tail.x;
            tail.y = head.y;
            break;
        case 'U':
            ++head.y;
            if (head.y != tail.y + 2) break;
            ++tail.y;
            tail.x = head.x;
            break;
        case 'D':
            --head.y;
            if (head.y != tail.y - 2) break;
            --tail.y;
            tail.x = head.x;
            break;
    };
    visited.insert(tail);
    std::cout << head.x << "," << head.y << " ; " << tail.x << "," << tail.y << " : " << visited.size() << "\n";
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
