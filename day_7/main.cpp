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

struct node {
    std::vector<node> children;
    node* parent;
    size_t size;
    std::string name;

    node (std::string nm, node* p) : name(nm), parent(p), size(0), children() {};
    size_t add_size (std::vector<size_t>& vec);
    std::string path ();
};

std::string node::path () {
    return (parent ? parent->path() : std::string{""}).append("/").append(name);
}

size_t node::add_size(std::vector<size_t>& vec) {
    for (auto &c : children) {
        size += c.add_size(vec);
    }
    vec.push_back(size);
   // std::cout << /*path() << ": " <<*/ size << "\n";
    return size;
}

int main () {

    node root{"/", nullptr};

    node *current = &root;

    while (1) {
        std::string line;
        std::getline(std::cin, line);
        if (std::cin.eof()) break;

        std::vector<std::string> pl;
        split (line, pl, ' ');
        if (pl[0] == "$") {
            if (pl[1] == "cd") {
                if (pl[2] == "..") {
                    current = current->parent;
                } else if (pl[2] == "/") {
                    current = &root;
                } else {
                    current->children.push_back(node{pl[2], current});
                    current = &(current->children.back());
                }
            } else {
            }
        } else if (pl[0] == "dir") {
        } else {
            current->size += stoi(pl[0]);
        }
    }
    
    
    std::cout << "here" << std::endl;


    std::vector<size_t> sizes;
    root.add_size (sizes);

    
    long long total = 0;

    for (auto &s : sizes) {
        if (s <= 100000) total += s;
    }

    std::cout << total << "\n";

    total = root.size;

    std::cout << total << "\n";

    long to_delete = total - 40000000;
    std::cout << "to delete: " << to_delete << "\n";

    std::sort(sizes.begin(), sizes.end());
    for (auto &s : sizes) {
        std::cout << s << "\n";
        if (s >= to_delete) break;
    }
}
