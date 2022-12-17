#include <iostream>
#include <vector>
#include <set>
#include <string>

// 0 <= x <= 6
struct point {
    int x, y;
};
bool operator< (const point a, const point b) {
    if (a.y < b.y) return true;
    if ((a.y == b.y) && (a.x < b.x)) return true;
    return false;
}
bool operator== (const point a, const point b) {
    return (a.x == b.x) && (a.y == b.y);
}

struct cache_t {
    int index;
    std::set<point> ground;
    long long piece;
    long long height;
};

//globals
std::string input {};
std::set<point> ground {{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0}};
long long erased_height = 0;
int input_index = 0;
constexpr long long n_pt1 = 2022;
constexpr long long n_pt2 = 1000000000000;
constexpr long long impassable_n = 3;
std::vector<cache_t> cache {};
long long  piece_number = 0;

std::vector<point> create_falling_piece (int height) {
    static int i = 0;

    std::vector<point> retval {};
    switch (i%5) {
        case 0:
            retval.push_back(point{2,height+4});
            retval.push_back(point{3,height+4});
            retval.push_back(point{4,height+4});
            retval.push_back(point{5,height+4});
            break;
        case 1:
            retval.push_back(point{2,height+5});
            retval.push_back(point{3,height+4});
            retval.push_back(point{3,height+5});
            retval.push_back(point{3,height+6});
            retval.push_back(point{4,height+5});
            break;
        case 2:
            retval.push_back(point{2,height+4});
            retval.push_back(point{3,height+4});
            retval.push_back(point{4,height+4});
            retval.push_back(point{4,height+5});
            retval.push_back(point{4,height+6});
            break;
        case 3:
            retval.push_back(point{2,height+4});
            retval.push_back(point{2,height+5});
            retval.push_back(point{2,height+6});
            retval.push_back(point{2,height+7});
            break;
        case 4:
            retval.push_back(point{2,height+4});
            retval.push_back(point{2,height+5});
            retval.push_back(point{3,height+4});
            retval.push_back(point{3,height+5});
            break;
    };
    ++i;
    return retval;
}

int get_height() {
    return ground.rbegin()->y;
}

void simulate_fall (std::vector<point> &rock) {
    std::vector<point> shifted_rock;
    bool shift;
    while (1) {
        //shift rock
        shifted_rock = rock;
        shift = true;
        int i = input_index % input.length();
        for (auto &p : shifted_rock) {
            if (input[i] == '<') {
                if (p.x == 0) shift = false;
                --p.x;
            } else {
                if (p.x == 6) shift = false;
                ++p.x;
            }
            if (ground.find(p) != ground.end()) shift = false;
        }
        if (shift) {
            rock = shifted_rock;
        }
        ++input_index;
        //drop rock
        shifted_rock = rock;
        shift = true;
        for (auto &p : shifted_rock) {
            --p.y;
            if (ground.find(p) != ground.end()) shift = false;
        }
        if (shift) {
            rock = shifted_rock;
        } else {
            break;
        }
    }
}

bool complete (int y) {
    for (int x = 0; x < 7; ++x) {
        bool b = true;
        for (int i = 0; i < impassable_n; ++i)
            b &= (ground.find(point{x,y-i}) == ground.end());
        if (b) return false;
    }
    return true;
}

void erase (int y) {
    static bool caching = true;

    std::set<point> new_ground {};
    for (auto it = ground.lower_bound(point{0,y}); it != ground.end(); ++it) {
        new_ground.insert(point{it->x, it->y - y});
    }
    ground = new_ground;
    erased_height += y;

    if (!caching) return;

    cache_t new_entry {input_index, new_ground, piece_number, erased_height};
    for (auto &entry : cache) {
        if ((((new_entry.index - entry.index) % input.length()) == 0)
            && (new_entry.ground == entry.ground)
            && ((new_entry.piece - entry.piece) % 5 == 0))
        {
            if (new_entry.piece <= n_pt1) break;

            std::cout << "cache hit!\n";
            std::cout << "old: piece number = " << entry.piece
                      << ", base height = " << entry.height << "\n";
            std::cout << "new: piece number = " << new_entry.piece
                      << ", base height = " << new_entry.height << "\n";

            int piece_diff = new_entry.piece - entry.piece;
            int height_diff = new_entry.height - entry.height;
            long long times = (n_pt2 - new_entry.piece) / piece_diff;
            piece_number += piece_diff * times;
            erased_height += height_diff * times;
            caching = false;

            std::cout << "forwarding to: piece number = " << piece_number
                      << ", base height = " << erased_height << "\n";
            break;
        }
    }
    cache.push_back(new_entry);
}

void update_ground (std::vector<point> &rock) {
    for (auto &p : rock) {
        if (!ground.insert(p).second)
            std::cout << "update failed\n";
    }
    int y = rock[0].y;
    if (complete(y)) {
        erase(y-impassable_n+1);
    }
}

int main () {
    getline (std::cin, input);

    for (; piece_number <= n_pt2-1; ++piece_number) {
        if (piece_number == n_pt1) {
            std::cout << "Part 1: " << erased_height + get_height() << "\n";
        }
        auto rock = create_falling_piece(get_height());
        simulate_fall(rock);
        update_ground(rock);
    }
    std::cout << "Part 2: " << erased_height + get_height() << "\n";
}
