#include <iostream>
#include <vector>

struct point {
    int x;
    int y;
};

#include "input.inc"

unsigned _abs(int a) {
    return a > 0 ? a : -a;
}

unsigned dist(point &a, point &b) {
    return _abs(a.x - b.x) + _abs(a.y - b.y);
}
constexpr int SIZE = 4000001;

bool x_loop (int &x, int y) {
    for (auto &pair : input) {
        auto d = dist(pair.first, pair.second);
        unsigned d_y = _abs(pair.first.y - y);
        long long diff = (long long)d - (long long)d_y;
        if (abs(x - pair.first.x) <= diff) {
            x = pair.first.x + diff;
            return false;
        }
    }
    // SOLUTION!!!
    std::cout << "Solution: " << (unsigned long long)x * (unsigned long long)(SIZE-1) + (unsigned long long)y << "\n";
    return true;
}

int main () {
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            if (x_loop (x,y)) return 0;
        }
    }
}
