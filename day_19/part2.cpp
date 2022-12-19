// this might take some time. For me:
// real	48m36.076s
// user	48m31.431s
// sys	0m0.440s

#include <iostream>
#include <vector>

struct input_t {
    int ore_ore;
    int clay_ore;
    int obsidian_ore;
    int obsidian_clay;
    int geode_ore;
    int geode_obsidian;
};

struct resource_t {
    int ore;
    int clay;
    int obsidian;
    int geode;
    int ore_robot;
    int clay_robot;
    int obsidian_robot;
    int geode_robot;

    resource_t () : ore(0)
                    , clay(0)
                    , obsidian(0)
                    , geode(0)
                    , ore_robot(1)
                    , clay_robot(0)
                    , obsidian_robot(0)
                    , geode_robot(0) {}
};

#include "input.inc"

int max = 0;
int turn_limit = 32;

int inf(resource_t r, int turns) {
    return r.geode + turns*r.geode_robot +
           (turns-1)*turns/2;
}

int max_geodes (input_t &b, resource_t r, int turns) {
    if (turns == 0) return r.geode;
    if (inf(r, turns) <= max) return 0;
    // factory
    std::vector<resource_t> posib{};
    posib.push_back(r);
    if (r.ore >= b.ore_ore) {
        resource_t p = r;
        p.ore -= b.ore_ore;
        p.ore_robot += 1;
        posib.push_back(p);
    }
    if (r.ore >= b.clay_ore) {
        resource_t p = r;
        p.ore -= b.clay_ore;
        p.clay_robot += 1;
        posib.push_back(p);
    }
    if ((r.ore >= b.obsidian_ore) && (r.clay >= b.obsidian_clay)) {
        resource_t p = r;
        p.ore -= b.obsidian_ore;
        p.clay -= b.obsidian_clay;
        p.obsidian_robot += 1;
        posib.push_back(p);
    }
    if ((r.ore >= b.geode_ore) && (r.obsidian >= b.geode_obsidian)) {
        resource_t p = r;
        p.ore -= b.geode_ore;
        p.obsidian -= b.geode_obsidian;
        p.geode_robot += 1;
        posib.push_back(p);
    }
    // robots
    auto robots = [&r](resource_t &_r) {
        _r.ore += r.ore_robot;
        _r.clay += r.clay_robot;
        _r.obsidian += r.obsidian_robot;
        _r.geode += r.geode_robot;
    };
    for (auto &_r : posib) {
        robots(_r);
    }
    //dfs
    int _max = r.geode;
    for (auto it = posib.rbegin(); it != posib.rend(); ++it) {
        int cand = max_geodes (b, *it, turns - 1);
        if (cand > _max) _max = cand;
    }
    if (_max > max) {
        max = _max;
    }
    return _max;
}

int main () {
    int prod = 1;
    for (int i = 1; i <= 3; ++i) {
        max = 0;
        max_geodes(input[i-1], resource_t(), turn_limit);
        std::cout << "blueprint " << i << ": " << max << "\n";
        prod *= max;
    }
    std::cout << "Part 2: " << prod << "\n";
}
