#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
std::vector<std::string> stacks
{
"QMGCL",
"RDLCTFHG",
"VJFNMTWR",
"JFDVQP",
"NFMSLBT",
"RNVHCDP",
"HCT",
"GSJVZNHP",
"ZFHG"
};
/*
std::vector<std::string> stacks
{
""
""
""
}
*/

void move (int n, int src, int dest) {
    while (n > 0) {
        char c = stacks[src].back();
        stacks[src].pop_back();
        stacks[dest].push_back(c);
        --n;
    }
}

int main () {
    while (1) {
        std::string str;
        int n, src, dest;
        std::getline(std::cin, str);
        if (std::cin.eof()) break;
        sscanf (str.c_str(), "move %d from %d to %d",&n, &src, &dest);
        move (n, src-1, dest-1);
        //std::cout << n << src << dest << "\n";
    }
    for (auto &x : stacks) {
        std::cout << x.back();
    }
        std::cout << "\n";
}
