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

//globals
std::string input {};
std::set<point> ground {{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0}};
long long erased_height = 0;
int input_index = 0;
constexpr long long n = 1000000000000;
//constexpr long long n = 10000;
std::vector<std::pair<int, std::set<point>>> cache {};



struct piece {
    std::vector<point> hitbox;
};
piece create_falling_piece (int height) {
    static int i = 0;

    piece retval {};
    switch (i%5) {
        case 0:
            retval.hitbox.push_back(point{2,height+4});
            retval.hitbox.push_back(point{3,height+4});
            retval.hitbox.push_back(point{4,height+4});
            retval.hitbox.push_back(point{5,height+4});
            break;
        case 1:
            retval.hitbox.push_back(point{2,height+5});
            retval.hitbox.push_back(point{3,height+4});
            retval.hitbox.push_back(point{3,height+5});
            retval.hitbox.push_back(point{3,height+6});
            retval.hitbox.push_back(point{4,height+5});
            break;
        case 2:
            retval.hitbox.push_back(point{2,height+4});
            retval.hitbox.push_back(point{3,height+4});
            retval.hitbox.push_back(point{4,height+4});
            retval.hitbox.push_back(point{4,height+5});
            retval.hitbox.push_back(point{4,height+6});
            break;
        case 3:
            retval.hitbox.push_back(point{2,height+4});
            retval.hitbox.push_back(point{2,height+5});
            retval.hitbox.push_back(point{2,height+6});
            retval.hitbox.push_back(point{2,height+7});
            break;
        case 4:
            retval.hitbox.push_back(point{2,height+4});
            retval.hitbox.push_back(point{2,height+5});
            retval.hitbox.push_back(point{3,height+4});
            retval.hitbox.push_back(point{3,height+5});
            break;
    };
    ++i;
    return retval;
}

int get_height() {
    return ground.rbegin()->y;
}


void simulate_fall (piece &rock) {

    piece shifted_rock;
    bool shift;
    while (1) {
        //shift rock
        shifted_rock = rock;
        shift = true;
        /*
        if (input_index >= input.length()) {
            std::cout << "end of input\n";
            input_index = 0;
        }
        */
        int i = input_index % input.length();
        for (auto &p : shifted_rock.hitbox) {
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
        for (auto &p : shifted_rock.hitbox) {
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
        if (ground.find(point{x,y}) == ground.end()) return false;
    }
    return true;
}

void erase (int y) {
    std::set<point> new_ground {};
    for (auto it = ground.find(point{0,y}); it != ground.end(); ++it) {
        new_ground.insert(point{it->x, it->y - y});
    }
    ground = new_ground;
    erased_height += (long long) y;
/*
    for (auto &pair : cache) {
        if ((((input_index - pair.first) % input.length()) == 0) && (pair.second == new_ground)) {
            std::cout << "cache hit on index " << input_index << "with previous" << pair.first << "\n";
        }
    }
    cache.emplace_back(input_index, new_ground);
*/
// input_index = 37922
// input_index = 7649
// input_diff : 0
}

void update_ground (piece &rock) {
    for (auto &p : rock.hitbox) {
        if (!ground.insert(p).second)
            std::cout << "update failed\n";
    }
    int y = rock.hitbox[0].y;
    if ((y >= 1000) && complete(y)) {
        //std::cout << "found complete row " << erased_height + (long long)y << "\n";
        erase(y);
    }
}
//7649: 1300 erased: 2029
//cache hit on index 37922with previous7649
//37922: 6400 erased: 9955

// i_diff = 5100.
// erased_diff = 7926

int main () {
    getline (std::cin, input);
    std::cout << input.length() << "\n";

    for (long long i = 0; i <= n-1; ++i) {
        auto rock = create_falling_piece(get_height());
        simulate_fall(rock);
        update_ground(rock);

        if (i == 1300) {
            while (i < n-1) {
                erased_height += 7926;
                i += 5100;
            }
            erased_height -= 7926;
            i -= 5100;
        }

/*
        if ((input_index == 37922) || (input_index == 7649))
            std::cout << input_index << ": " << i << " erased: " << erased_height << "\n";
*/
//        for (auto &p : ground) {
            //std::cout << "(" << p.x << "," << p.y << "), ";
//        }
//        std::cout << "\n";
    }

    std::cout << erased_height + (long long)get_height() << "\n";
}
