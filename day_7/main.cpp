#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

size_t add_size(std::vector<size_t>& vec) {
    size_t size = 0;
    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) break;

        std::vector<std::string> pl;
        split (line, pl, ' ');

        if (pl[0] == "dir") continue;
        if (pl[0] == "$") {
            if (pl[1] != "cd") continue;
            if (pl[2] == "..") break;
            size += add_size(vec);
            if (std::cin.eof()) break;
            continue;
        }
        size += stoi(pl[0]);
    }
    vec.push_back(size);
    return size;
}

int main () {
    // get rid of cd /
    std::string dummy;
    std::getline(std::cin, dummy);

    std::vector<size_t> sizes;
    size_t total = add_size (sizes);

    size_t part1 = 0;

    for (auto &s : sizes) {
        if (s <= 100000) part1 += s;
    }

    std::cout << part1 << "\n";

    long to_delete = total - 40000000;

    std::sort(sizes.begin(), sizes.end());
    for (auto &s : sizes) {
        if (s >= to_delete) {
            std::cout << s << "\n";
            break;
        }
    }
}
