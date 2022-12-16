#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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
//#include "test_input.inc"

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
    const std::string &current_valve,
    std::vector<std::string> open_valves)
{
    //std::cout << remaining_moves << "\n";
    auto cur_it = find_valve(input, current_valve);
    if (cur_it == input.end()) {
        std::cout << "valve " << current_valve << " not found!\n";
        return 0;
    }
    open_valves.push_back(current_valve);
    int max_pressure = released_pressure + flowrate + (flowrate + cur_it->flowrate) * remaining_moves;
    for (auto it : cur_it->tunnels) {
        if (std::find(open_valves.begin(), open_valves.end(), it.first) != open_valves.end()) continue;
        if (it.second < remaining_moves-1) {
            int candidate = dsf(
                remaining_moves - it.second - 1,
                flowrate + cur_it->flowrate,
                released_pressure + flowrate + (flowrate + cur_it->flowrate) * it.second,
                it.first,
                open_valves);

            if (candidate > max_pressure) max_pressure = candidate;
        }
    }
    return max_pressure;
}

std::map<std::string, int>::iterator get_lowest(std::map<std::string, int> &t, std::vector<std::string> &except) {
    auto lowest_it = t.end();
    for (auto t_it = t.begin(); t_it != t.end(); ++t_it) {
        if (std::find(except.begin(), except.end(), t_it->first) != except.end()) continue;
        if (lowest_it == t.end()) lowest_it = t_it;
        if (lowest_it->second > t_it->second) lowest_it = t_it;
    }
    return lowest_it;
}

void update (std::vector<valve> &valve_vector, std::vector<valve>::iterator update_valve_it) {
    std::vector<std::string> updated;
    auto &t = update_valve_it->tunnels;
    // add all other valves to tunnel list
    for (auto v : valve_vector) {
        if (v.name == update_valve_it->name) continue;
        auto t_it = t.find(v.name);
        if(t_it == t.end()) {
            t[v.name] = 1000;
        }
    }
    // update eacj tunnel
    while (updated.size() < t.size()) {
        auto lowest_it = get_lowest(t, updated);
        updated.push_back(lowest_it->first);
        for (auto &tun : find_valve(valve_vector, lowest_it->first)->tunnels) {
            if (tun.first == update_valve_it->name) continue;
            if (t[tun.first] > lowest_it->second + tun.second)
                t[tun.first] = lowest_it->second + tun.second;
        }
    }
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
    for (auto it = input.begin(); it != input.end(); ++it) {
        update(input, it);
    }

    for (auto &v : input) {
        print_valve(v);
    }

    std::cout << dsf(30, 0, 0, "AA", std::vector<std::string>{}) << "\n";
}
