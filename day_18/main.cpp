#include <iostream>
#include <set>
#include <climits>
#include <queue>

struct point {
    int x,y,z;
};
bool operator< (const point a, const point b) {
    if (a.x < b.x) return true;
    if (a.x > b.x) return false;
    if (a.y < b.y) return true;
    if (a.y > b.y) return false;
    return a.z < b.z;
}

#include "input.inc"

void print (point &p) {
    std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}
point max{INT_MIN, INT_MIN, INT_MIN}, min{INT_MAX, INT_MAX, INT_MAX};

bool try_escape (point start) {

    static std::set<point> escape_cache {};

    std::queue<point> check_set {};
    check_set.push(start);
    std::set<point> escape_set {};
    while (!check_set.empty()) {
        point p = check_set.front();
        check_set.pop();
        if ((escape_set.find(p) != escape_set.end())
          ||(escape_cache.find(p) != escape_cache.end())
          ||(input.find(p) != input.end())) continue;

        escape_set.insert(p);

        if ((p.x > max.x)
        || (p.x < min.x)
        || (p.y > max.y)
        || (p.y < min.y)
        || (p.z > max.z)
        || (p.z < min.z)) {
            //escaped
            return true;
        }

        check_set.push(point{p.x+1,p.y+0,p.z+0});
        check_set.push(point{p.x-1,p.y+0,p.z+0});
        check_set.push(point{p.x+0,p.y+1,p.z+0});
        check_set.push(point{p.x+0,p.y-1,p.z+0});
        check_set.push(point{p.x+0,p.y+0,p.z+1});
        check_set.push(point{p.x+0,p.y+0,p.z-1});
    }
    // didn't escape
    for (auto &p : escape_set)
        escape_cache.insert(p);
    return false;
}

int main () {

    int sides = 0;
    for (auto &p : input) {
        if (input.find(point{p.x+1,p.y+0,p.z+0}) == input.end()) ++sides;
        if (input.find(point{p.x-1,p.y+0,p.z+0}) == input.end()) ++sides;
        if (input.find(point{p.x+0,p.y+1,p.z+0}) == input.end()) ++sides;
        if (input.find(point{p.x+0,p.y-1,p.z+0}) == input.end()) ++sides;
        if (input.find(point{p.x+0,p.y+0,p.z+1}) == input.end()) ++sides;
        if (input.find(point{p.x+0,p.y+0,p.z-1}) == input.end()) ++sides;
        if (p.x > max.x) max.x = p.x;
        if (p.x < min.x) min.x = p.x;
        if (p.y > max.y) max.y = p.y;
        if (p.y < min.y) min.y = p.y;
        if (p.z > max.z) max.z = p.z;
        if (p.z < min.z) min.z = p.z;
    }
    std::cout << "min: ";
    print(min);
    std::cout << "\nmax: ";
    print(max);
    std::cout << "\n";

    std::cout << "part 1: " << sides << "\n";

    sides = 0;
    for (auto &p : input) {
        if (try_escape(point{p.x+1,p.y+0,p.z+0})) ++sides;
        if (try_escape(point{p.x-1,p.y+0,p.z+0})) ++sides;
        if (try_escape(point{p.x+0,p.y+1,p.z+0})) ++sides;
        if (try_escape(point{p.x+0,p.y-1,p.z+0})) ++sides;
        if (try_escape(point{p.x+0,p.y+0,p.z+1})) ++sides;
        if (try_escape(point{p.x+0,p.y+0,p.z-1})) ++sides;
    }
    std::cout << "part 2: " << sides << "\n";
}
