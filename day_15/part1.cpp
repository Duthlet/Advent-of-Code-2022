#include <iostream>
#include <vector>
#include <set>

struct point {
    int x;
    int y;
};

#include "input.inc"

bool operator< (const point a, const point b) {
    if (a.x < b.x) return true;
    if (a.x > b.x) return false;
    return a.y < b.y;
}

unsigned _abs(int a) {
    return a > 0 ? a : -a;
}

unsigned dist(point &a, point &b) {
    return _abs(a.x - b.x) + _abs(a.y - b.y);
}

int main () {
    int y=2000000;
    std::set<int> impossible{};

    for (auto &pair : input) {
        auto d = dist(pair.first, pair.second);
        unsigned d_y = _abs(pair.first.y - y);
        long long diff = (long long)d - (long long)d_y;
        if (diff < 0) continue;
        for (int x = pair.first.x - diff; x <= pair.first.x + diff; ++x) {
            impossible.insert(x);
        }
    }

    for (auto &pair : input) {
        if (pair.second.y == y) {
            impossible.erase(pair.second.x);
        }
    }

    std::cout << impossible.size() << "\n";
}
