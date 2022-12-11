#include <iostream>
#include <string>
#include <vector>
#include <climits>

struct monkey;

bool done = false;
long long modulus = 243;
std::vector<monkey*> Monkey;

struct monkey {
    monkey();

    std::vector<long long> items;
    int div_by;
    int throw_to[2];
    std::string op_str;

    int count = 0;

    long long op(long long x);
    void turn();
};

monkey::monkey () {
    std::string line;
/*
Monkey 0:
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
/*
  Starting items: 89, 84, 88, 78, 70
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
    line = line.substr(16, std::string::npos);

    items = {};
    while (line != "") {
        line = line.substr(1, std::string::npos);
        size_t pos;
        items.push_back(stoi(line, &pos));
        line = line.substr(pos, std::string::npos);
    }
/*
  Operation: new = old * 5
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
    op_str = line.substr(23, std::string::npos);
/*
  Test: divisible by 7
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
    div_by = stoi(line.substr(21, std::string::npos));
/*
    If true: throw to monkey 6
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
    throw_to[0] = stoi(line.substr(29, std::string::npos));
/*
    If false: throw to monkey 7
*/
    std::getline(std::cin, line);
    if (std::cin.eof()) {
        done = true;
        return;
    }
    throw_to[1] = stoi(line.substr(30, std::string::npos));
/*

*/
    std::getline(std::cin, line);
}

long long monkey::op (long long x) {
    if (op_str.substr(2,std::string::npos) == "old") {
        return x * x;
    }
    int y = stoi(op_str.substr(2,std::string::npos));
    if (op_str[0] == '*') {
        return x * y;
    }
    return x + y;
}

void monkey::turn() {
    for (auto x : items) {
        ++count;
        if (x >= (long long)INT_MAX) {
            std::cout << "!!!WARNING!!!\n";
        }
        long long y = (op(x)/3) % modulus;
        Monkey[throw_to[!!(y%div_by)]]->items.push_back(y);
    }
    items.clear();
}

void init() {
    while (1) {
        auto m = new monkey();
        if (done) return;
        Monkey.push_back(m);
        modulus *= m->div_by;
    }
}

void round() {
    for (auto m : Monkey) {
        for (auto &x : m->items)
        m->turn();
    }
}

int main () {
    init();
    for (int i = 0; i < 20; ++i) {
        round();
    }

    long long m1 = 0, m2 = 0;

    for (auto m : Monkey) {
        if (m->count > m1) {
            m2 = m1;
            m1 = m->count;
            continue;
        }
        if (m->count > m2) {
            m2 = m->count;
        }
    }

    std::cout << m1 * m2 << "\n";
}
