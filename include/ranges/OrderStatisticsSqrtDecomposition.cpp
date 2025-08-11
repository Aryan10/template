#include <bits/stdc++.h>
using namespace std;

struct OrderStatistics {
    static constexpr int SHIFT_SMALL = 9;      // block size = 2^9 = 512
    static constexpr int SHIFT_BIG   = 18;     // total size = 2^18 = 262144
    static constexpr int BLOCK_SIZE  = 1 << SHIFT_SMALL;
    static constexpr int N           = 1 << SHIFT_BIG;

    vector<int> small; // freq per value
    vector<int> big;   // freq per block

    OrderStatistics() : small(N, 0), big(N / BLOCK_SIZE, 0) {}

    // insert value in O(1)
    inline void insert(int x) {
        ++small[x];
        ++big[x >> SHIFT_SMALL];
    }

    // erase value in O(1)
    inline void erase(int x) {
        if (small[x] > 0) {
            --small[x];
            --big[x >> SHIFT_SMALL];
        }
    }

    // kth element in O(sqrt n)
    inline int kth_element(int k) const {
        int block = 0;
        while (big[block] <= k) k -= big[block++];
        int val = block << SHIFT_SMALL;
        while (small[val] <= k) k -= small[val++];
        return val;
    }

    // size in O(sqrt n)
    inline int size() const {
        return accumulate(big.begin(), big.end(), 0);
    }
};