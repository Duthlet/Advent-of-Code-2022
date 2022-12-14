#include <iostream>
#include <vector>
#include <set>
#include <unistd.h>

struct point {
    int x;
    int y;
};

#include "input.inc"
/*
std::vector<std::vector<point> > input
{{{498,4 }, { 498,6 }, { 496,6}},
{{503,4 }, { 502,4 }, { 502,9 }, { 494,9}}};
*/

bool operator< (const point a, const point b) {
    if (a.x < b.x) return true;
    if (a.x > b.x) return false;
    return a.y < b.y;
}

int sgn (int x) {
    if (x < 0) return -1;
    return x > 0;
}

std::set<point> filled {};
int max_y = 0;
int min_x = 500, max_x = 500;

bool add_grain() {
    for (point pos {500, 0}; pos.y <= max_y; ++pos.y) {
        if (filled.find(pos) != filled.end()) {
            --pos.x;
            if (filled.find(pos) != filled.end()) {
                pos.x += 2;
                if (filled.find(pos) != filled.end()) {
                    // no space
                    --pos.x;
                    --pos.y;
                    if (!filled.insert(pos).second) {
                        std::cout << pos.x << "," << pos.y << "already filled\n";
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void draw_mirrored() {
    point p;
//    std::cout << "\033[2J\033[1;1H"; // clear screen
    for (p.x = min_x; p.x <= max_x; ++p.x) {
        for (p.y = max_y; p.y >= 0 ;--p.y) {
            std::cout << (filled.find(p) == filled.end() ? '.' : '#');
        }
        std::cout << "\n";
    }
}
void draw() {
    point p;
//    std::cout << "\033[2J\033[1;1H"; // clear screen
    for (p.y = 0; p.y <= max_y; ++p.y) {
        for (p.x = min_x; p.x <= max_x; ++p.x) {
            if ((p.x == 500) && (p.y == 0)) std::cout << '+';
            else std::cout << (filled.find(p) == filled.end() ? '.' : '#');
        }
        std::cout << "\n";
    }
}

int main () {

    for (auto &path : input) {
        for (auto it = path.begin(), old = it++; it != path.end(); ++it, ++old) {
            //add path from old to it
            if (old->x == it->x) {
                int dir = sgn(it->y - old->y);
                for (int cur = old->y; cur != it->y; cur += dir) {
                    filled.insert(point{it->x, cur});
                }

            } else {
                int dir = sgn(it->x - old->x);
                for (int cur = old->x; cur != it->x; cur += dir) {
                    filled.insert(point{cur, it->y});
                }
            }
            filled.insert(*it);
        }
    }

    for (auto &p : filled) {
        if (p.y > max_y) max_y = p.y;
        if (p.x > max_x) max_x = p.x;
        if (p.x < min_x) min_x = p.x;
    }
    std::cout << min_x << " <= x <= " << max_x << "\n";
    std::cout << "max y: " << max_y << "\n";
    int cnt;
    draw();
    std::cout << "\n";
    for (cnt = 0; add_grain(); ++cnt) {
  //      draw_mirrored();
//        usleep(1000*100);
    }
    draw();
    std::cout << "grains: " << cnt << "\n";
}
