#include <iostream>
#include <vector>
#include <list>

#include "input.inc"
/*std::vector<long long> input
{1,
2,
-3,
3,
-2,
0,
4};*/
int size;
std::list<int> shuffled {};

void shuffle() {
    for (int n = 0; n < size; ++n) {
        auto it = shuffled.begin();
        for (; it != shuffled.end(); ++it) if (*it == n) break;
        if (it == shuffled.end()) std::cout << "oops\n";

//        for (auto &x : shuffled) std::cout << input[x] << ", ";
//        std::cout << "\n";

        it = shuffled.erase(it);
        long long cnt = input[n] % (size-1);
        if (cnt < 0) cnt += (size-1);

//        std::cout << "moving " << input[n] << " by " << cnt << "(mod " << size-1<< ")\n";

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

int main () {
    size = input.size();
    for (int i = 0; i < size; ++i) {
        shuffled.push_back(i);
    }

    long long key = 811589153;
    for (auto &i : input) i *= key;

//        for (auto &x : shuffled) std::cout << input[x] << ", ";
//        std::cout << "\n";
    for (int i = 0; i < 10; ++i) {
    shuffle();
}
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
    std::cout << sum << "\n";
}
