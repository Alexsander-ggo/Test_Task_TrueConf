#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "container_holder.h"

using namespace ch;
using namespace std;

using num = int;
using index = int;

const size_t MIN = 1;
const size_t MAX = 30;
const size_t ERASE = 15;

num RandNum(num from, num to) {
    return rand() % (to - from + 1) + from;
}

template <typename Key, typename Value>
ostream& operator<<(ostream& out, const pair<Key, Value>& pair) {
    return out << pair.first << " "s << pair.second;
}

int main() {
    srand(time(NULL));
   
    ContainerHolder<vector<num>> holder_vector;
    ContainerHolder<map<index, num>> holder_map;

    holder_vector.Add(RandNum(MIN, MAX), [](auto& cont, index) {
        cont.push_back(RandNum(1, 9));
        });
    holder_vector.Print();

    holder_map.Add(RandNum(MIN, MAX), [](auto& cont, index id) {
        cont[id] = RandNum(1, 9);
        });
    holder_map.Print();


    holder_vector.Erase(RandNum(0, ERASE), [](auto& cont) {
        cont.erase(cont.begin() + RandNum(0, cont.size() - 1));
        });
    holder_vector.Print();

    holder_map.Erase(RandNum(0, ERASE), [](auto& cont) {
        cont.erase(RandNum(0, cont.size() - 1));
        });
    holder_map.Print();

    holder_vector.Syncing(holder_map.Begin(), holder_map.End(),
        [](auto begin, auto end, auto it) {
            return find_if(begin, end, [it](const auto& pair) {
                return pair.second == *it;
                }) != end;
        },
        [](auto& cont, auto it) {
            cont.push_back(*it);
        });
    holder_vector.Print();

    holder_map.Syncing(holder_vector.Begin(), holder_vector.End(),
        [](auto begin, auto end, auto it) {
            return find_if(begin, end, [it](const auto& num) {
                return num == it->second;
                }) != end;
        },
        [](auto& cont, auto it) {
            cont.insert(*it);
        });
    holder_map.Print();

    return 0;
}