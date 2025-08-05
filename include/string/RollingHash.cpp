#include <bits/stdc++.h>
using namespace std;

struct RollingHash {
    vector<int> hash, powers;
    static constexpr int P = 31;
    static constexpr int mod = 1e9 + 9;

    RollingHash(const string& s) : hash(s.size() + 1, 0), powers(s.size() + 1, 1) {
        for (int i = 0; i < s.size(); ++i) {
            hash[i + 1] = (1LL * hash[i] * P + s[i]) % mod;
            powers[i + 1] = (1LL * powers[i] * P) % mod;
        }
    }

    int substr(int l, int r) {
        return (1LL * hash[r + 1] - (1LL * hash[l] * powers[r - l + 1] % mod) + mod) % mod;
    }
};