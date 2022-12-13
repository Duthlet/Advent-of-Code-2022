#include <iostream>
#include <vector>
#include <string>


std::string get_first(std::string &in) {
    // empty list
    if (in[1] == ']') {
        in = "";
        return "";
    }
    // nonempty list
    if (in[1] == '[') {
        int count = 1;
        for (int i =2; i < in.length()-1 ;++i) {
            if (in[i] == '[') {
                ++count;
            } else if (in[i] == ']') {
                --count;
                if (!count) {
                    auto result = in.substr(1, i);
                    if (in[i+1] == ',') {
                        ++i;
                    }
                    in.erase(1,i);
                    return result;
                }
            }
        }
        std::cerr << "no matching ']'\n";
    }
    // integer
    auto i = in.find_first_not_of("1234567890", 1);
    if (i == std::string::npos) {
        std::cerr << "i = npos\n";
    }
    auto result = in.substr(1, i-1);
    if (in[i] == ',') {
        ++i;
    }
    in.erase(1,i-1);
    return result;
}

void listify (std::string &in) {
    if (in[0] != '[') {
        in.insert(in.begin(),'[');
        in.append(1,']');
    }
}

int compare_pair (std::string &left, std::string &right) {
    if (left == right) return 0;
    if (left.empty()) return 1;
    if (right.empty()) return -1;
    if ((left[0] != '[') && (right[0] != '[')) {
        int r = stoi(right);
        int l = stoi(left);
        if (r < l) return -1;
        return l < r;
    }
    listify (left);
    listify (right);
    // now we have two lists
    while (1) {
        std::string first_left = get_first(left);
        std::string first_right = get_first(right);
        int i = compare_pair(first_left, first_right);
        if (i) return i;

        if (left == right) return 0;
        if (left.empty()) return 1;
        if (right.empty()) return -1;
    }
    return 0;
}

int part2 (const std::string &org, std::vector <std::string> &lines) {
    int i = 0;
    for (auto line : lines) {
        std::string cp = org;
        if (compare_pair(cp, line) == -1) ++i;
    }
    return i;
}

int main () {
    int sum = 0;
    int i = 0;
    std::vector <std::string> lines {};
    while (1) {
        ++i;
        std::string left, right;
        std::getline(std::cin, left);
        std::getline(std::cin, right);
        if (std::cin.eof()) {
            break;
        }
        lines.push_back(left);
        lines.push_back(right);
        // for part 1
        int comp = compare_pair(left, right);
        if (comp == 0) {
            std::cout << "equal lists\n";
        }
        if (comp == 1) {
            sum += i;
        }
        std::getline(std::cin, left); //empty line
    }
    std::cout << "Part 1: " << sum << "\n";
    // part 2
    int pt2 = (part2 ("[[2]]", lines) + 1)* (part2 ("[[6]]", lines) + 2);
    std::cout << "Part 2: " << pt2 << "\n";
}
