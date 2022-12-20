#include <iostream>
#include <vector>
#include <list>

#include "input.inc"

int size;
std::list<int> shuffled;

void shuffle() {
    for (int n = 0; n < size; ++n) {
        auto it = shuffled.begin();
        for (; it != shuffled.end(); ++it) if (*it == n) break;
        if (it == shuffled.end()) std::cout << "oops\n";

        it = shuffled.erase(it);
        long long cnt = input[n] % (size-1);
        if (cnt < 0) cnt += (size-1);
        while (cnt > 0) {
            if (it == shuffled.end()) {
                it = shuffled.begin();
            }
            ++it;
            --cnt;
        }
        shuffled.insert(it, n);
    }
}

long long get_sum () {
    long long sum = 0;
    auto it = shuffled.begin();
    for (; it != shuffled.end(); ++it) if (input[*it] == 0) break;

    for (int cnt = 0; cnt < 3; ++cnt) {
        for (int i = 0; i < 1000; ++i) {
            ++it;
            if (it == shuffled.end()) it = shuffled.begin();
        }
        sum += input[*it];
    }
    return sum;
}

void part1 () {
    shuffled = std::list<int> {};
    for (int i = 0; i < size; ++i) {
        shuffled.push_back(i);
    }
    shuffle();
    std::cout << "Part 1: " << get_sum() << "\n";
}

void part2 () {
    long long key = 811589153;
    for (auto &i : input) i *= key;

    shuffled = std::list<int> {};
    for (int i = 0; i < size; ++i) {
        shuffled.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        shuffle();
    }
    std::cout << "Part 2: " << get_sum() << "\n";
}

int main () {
    size = input.size();
    part1();
    part2();
}
