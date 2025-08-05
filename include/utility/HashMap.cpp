#include <bits/stdc++.h>
using namespace std;

mt19937 rng{static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count())};
struct RandomizedHash {
    size_t operator()(uint64_t x) const {
        static const uint64_t LOCK = rng();
        return x ^ LOCK;
    }
};

template <typename Map>
Map reserveHashMap(int default_capacity = 512, double default_load_factor = 0.25) {
    Map m;
    m.reserve(default_capacity);
    m.max_load_factor(default_load_factor);
    return m;
}

// Usage: auto mp = reserveHashMap<unordered_map<int, int, RandomizedHash>>();