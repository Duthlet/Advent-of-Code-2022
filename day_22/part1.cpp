#include <iostream>
#include <vector>
#include <string>

#include "input.inc"
//Facing is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^).
enum class direction {
    right = 0,
    down = 1,
    left = 2,
    up = 3};

direction dir;
int x, y;

void step_right () {
    int new_x = x+1;
    if ((map[y].length() <= new_x) || (map[y][new_x] == ' ')) {
        //wrap around
        new_x = map[y].find_first_not_of(' ');
        if (new_x == std::string::npos) return;
    }
    if (map[y][new_x] == '.') x = new_x;
}
void step_left () {
    int new_x = x-1;
    if ((0 > new_x) || (map[y][new_x] == ' ')) {
        //wrap around
        new_x = map[y].find_last_not_of(' ');
        if (new_x == std::string::npos) return;
    }
    if (map[y][new_x] == '.') x = new_x;
}
void step_up () {
    int new_y = y-1;
    if ((0 > new_y) || (map[new_y].length() <= x) || (map[new_y][x] == ' ')) {
        //wrap around
        for (new_y = map.size()-1; new_y >= 0; --new_y) {
            if ((map[new_y].length() > x) && (map[new_y][x] != ' ')) break;
        }
        if (new_y < 0) return;
    }
    if (map[new_y][x] == '.') y = new_y;
}
void step_down () {
    int new_y = y+1;
    if ((map.size() <= new_y) || (map[new_y].length() <= x) || (map[new_y][x] == ' ')) {
        //wrap around
        for (new_y = 0; new_y < map.size(); ++new_y) {
            if ((map[new_y].length() > x) && (map[new_y][x] != ' ')) break;
        }
        if (new_y >= map.size()) return;
    }
    if (map[new_y][x] == '.') y = new_y;
}

void turn (char c) {
    if (c == 'R') {
        switch (dir) {
            case direction::up :
                dir = direction::right;
                break;
            case direction::right :
                dir = direction::down;
                break;
            case direction::down :
                dir = direction::left;
                break;
            case direction::left :
                dir = direction::up;
                break;
        }
    }
    if (c == 'L') {
        switch (dir) {
            case direction::up :
                dir = direction::left;
                break;
            case direction::right :
                dir = direction::up;
                break;
            case direction::down :
                dir = direction::right;
                break;
            case direction::left :
                dir = direction::down;
                break;
        }
    }
}

void move() {
    switch (dir) {
        case direction::up :
            step_up();
            break;
        case direction::right :
            step_right();
            break;
        case direction::down :
            step_down();
            break;
        case direction::left :
            step_left();
            break;
    }
}

int get_number(int &i)
{
    int j = i;
    for (; i < moves.length() && std::isdigit(moves[i]); ++i);
    return std::stoi(moves.substr(j, i-j));
}

void part1() {
    int i = 0;
    while (i < moves.length()) {
        for (int j = get_number(i); j > 0; --j) {
            move();
        }
        if (i >= moves.length()) return;
        turn (moves[i]);
        ++i;
    }
}

int main () {
    y = 0;
    x = map[y].find_first_of('.');
    dir = direction::right;
    part1();
//    The final password is the sum of 1000 times the row, 4 times the column, and the facing.
    std::cout << 1000 * (y+1) + 4*(x+1) + static_cast<int>(dir)  << "\n";
}
