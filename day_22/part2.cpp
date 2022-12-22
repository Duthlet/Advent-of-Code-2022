#include <iostream>
#include <vector>
#include <string>

// 50*50 blocks
//
// layout:
//  12
//  3
// 56
// 4
//up:
//    1 -> 4 right
//    2 -> 4 up
//    5 -> 3 right
//down:
//    2 -> 3 left
//    6 -> 4 left
//    4 -> 2 down
//right:
//    2 -> 6 left
//    3 -> 2 up
//    6 -> 2 left
//    4 -> 6 up
//left:
//    1 -> 5 right
//    3 -> 5 down
//    5 -> 1 right
//    4 -> 1 down

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
    int new_y = y;
    direction new_dir = dir;
    if ((map[y].length() <= new_x) || (map[y][new_x] == ' ')) {
        //wrap around
        if (0 <= y && y < 50) {
//    2 -> 6 left
            new_x = 99;
            new_y = 149 - y;
            new_dir = direction::left;
        } else if (50 <= y && y < 100) {
//    3 -> 2 up
            new_x = y + 50;
            new_y = 49;
            new_dir = direction::up;
        } else if (100 <= y && y < 150) {
//    6 -> 2 left
            new_x = 149;
            new_y = 49 - (y - 100);
            new_dir = direction::left;
        } else  { //if (150 <= y < 200) {
//    4 -> 6 up
            new_x = y - 100; //y 150 -> x 50
            new_y = 149;
            new_dir = direction::up;
        }
    }
    if (map[new_y][new_x] != '.') return;
    x = new_x;
    y = new_y;
    dir = new_dir;
}
void step_left () {
    int new_x = x-1;
    int new_y = y;
    direction new_dir = dir;
    if ((0 > new_x) || (map[y][new_x] == ' ')) {
        //wrap around
        if (0 <= y && y < 50) {
//    1 -> 5 right
            new_x = 0;
            new_y = 149 - y;
            new_dir = direction::right;
        } else if (50 <= y && y < 100) {
//    3 -> 5 down
            new_x = y - 50;
            new_y = 100;
            new_dir = direction::down;
        } else if (100 <= y && y < 150) {
//    5 -> 1 right
            new_x = 50;
            new_y = 149 - y;
            new_dir = direction::right;
        } else  { //if (150 <= y < 200) {
//    4 -> 1 down
            new_x = y - 100; //y = 150 -> 50
            new_y = 0;
            new_dir = direction::down;
        }
    }
    if (map[new_y][new_x] != '.') return;
    x = new_x;
    y = new_y;
    dir = new_dir;
}
void step_up () {
    int new_y = y-1;
    int new_x = x;
    direction new_dir = dir;
    if ((0 > new_y) || (map[new_y].length() <= x) || (map[new_y][x] == ' ')) {
        //wrap around
        if (0 <= x && x < 50) {
//    5 -> 3 right
            new_x = 50;
            new_y = x + 50;
            new_dir = direction::right;
        } else if (50 <= x && x < 100) {
//    1 -> 4 right
            new_x = 0;
            new_y = 100 + x;
            new_dir = direction::right;
        } else { //if (100 <= x < 150) {
//    2 -> 4 up
            new_x = x - 100;
            new_y = 199;
            new_dir = direction::up;
        }
    }
    if (map[new_y][new_x] != '.') return;
    x = new_x;
    y = new_y;
    dir = new_dir;
}
void step_down () {
    int new_y = y+1;
    int new_x = x;
    direction new_dir = dir;
    if ((map.size() <= new_y) || (map[new_y].length() <= x) || (map[new_y][x] == ' ')) {
        //wrap around
        if (0 <= x && x < 50) {
//    4 -> 2 down
            new_x = x + 100;
            new_y = 0;
            new_dir = direction::down;
        } else if (50 <= x && x < 100) {
//    6 -> 4 left
            new_x = 49;
            new_y = x + 100; // x 50 -> y 150
            new_dir = direction::left;
        } else { //if (100 <= x < 150) {
//    2 -> 3 left
            new_x = 99;
            new_y = x - 50; // x 100 -> y 50
            new_dir = direction::left;
        }
    }
    if (map[new_y][new_x] != '.') return;
    x = new_x;
    y = new_y;
    dir = new_dir;
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
