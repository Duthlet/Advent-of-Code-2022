#include <iostream>
#include <vector>
#include <string>
#include <map>

struct valve {
    valve(std::string _name, int _fr, std::vector<std::string>_tun) : name(_name), flowrate(_fr), tunnels() {
        for (auto &s: _tun) {
            tunnels.emplace(s, 1);
        }
    }

    std::string name;
    int flowrate;
    std::map<std::string, int> tunnels;
};

#include "input.inc"

void print_valve (valve &v) {
    std::cout << "Valve " << v.name << ": flowrate = " << v.flowrate
        << ", tunnels = ";
    for (auto &p : v.tunnels) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << "\n";
}


void replace_valve (std::vector<valve> &valve_vector, std::vector<valve>::iterator replace_valve_it) {
    valve &v0 = *replace_valve_it;
    for (auto &v : valve_vector) {
        if (v.name == v0.name) continue;
        auto replace_it = v.tunnels.find(v0.name);
        if (replace_it == v.tunnels.end()) continue;

        for (auto &p0 : v0.tunnels) {
            int length = replace_it->second + p0.second;
            auto it = v.tunnels.find(p0.first);
            if (it == v.tunnels.end()) {
                if (p0.first != v.name) {
                    v.tunnels[p0.first] = length;
                }
                continue;
            }
            if (it->second > length) it->second = length;
        }

        v.tunnels.erase(replace_it);
    }
    valve_vector.erase(replace_valve_it);
}

std::vector<valve>::iterator find_valve (std::vector<valve> &vec, const std::string &name) {
    auto cur_it = vec.begin();
    while (cur_it != vec.end()) {
        if(cur_it->name == name) break;
        ++cur_it;
    }
    return cur_it;
}

int dsf(
    int remaining_moves,
    int flowrate,
    int released_pressure,
    std::vector<valve> &valves,
    const std::string &current_valve)
{
    int max_pressure = released_pressure + flowrate * remaining_moves;
    auto cur_it = find_valve(valves, current_valve);
    if (cur_it == valves.end()) {
        std::cout << "valve " << current_valve << " not found!\n";
        return 0;
    }
    // don't turn on valve
    for (auto it : cur_it->tunnels) {
        if (it.second < remaining_moves) {
            int candidate = dsf(
                remaining_moves - it.second,
                flowrate,
                released_pressure + flowrate * it.second,
                valves,
                it.first);

            if (candidate > max_pressure) max_pressure = candidate;
        }
    }
    // turn on valve
    {
        int candidate = released_pressure + flowrate
                        + (flowrate + cur_it->flowrate) * (remaining_moves - 1);
        if (candidate > max_pressure) max_pressure = candidate;
    }
    for (auto it : cur_it->tunnels) {
        if (it.second < remaining_moves-1) {
            auto new_valves = valves;
            auto new_it = find_valve(new_valves, current_valve);
            if (new_it == new_valves.end()) {
                std::cout << "valve " << current_valve << " not found (in new vector)!\n";
                return 0;
            }
            replace_valve(new_valves, new_it);

            int candidate = dsf(
                remaining_moves - it.second - 1,
                flowrate + cur_it->flowrate,
                released_pressure + flowrate + (flowrate + cur_it->flowrate) * it.second,
                new_valves,
                it.first);

            if (candidate > max_pressure) max_pressure = candidate;
        }
    }

    return max_pressure;
}

int main () {
    for (auto it = input.begin(); it != input.end();) {
        if ((it->flowrate == 0) && (it->name != "AA")) {
            replace_valve(input, it);
            it = input.begin();
        } else {
            ++it;
        }
    }

    for (auto &v : input) {
        print_valve(v);
    }

    std::cout << dsf(30, 0, 0, input, "AA") << "\n";
}
