#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Merge = plus<T>>
class FenwickTree {
    int n;
    T identity;
    vector<T> BIT;
    function<T(T, T)> merge;

public:
    FenwickTree(int n, T identity = T(), function<T(T, T)> merge = Merge())
    : n(n), identity(identity), merge(merge), BIT(n + 1, identity) {}

    FenwickTree(vector<int> const& arr, T identity = T(), function<T(T, T)> merge = Merge())
    : FenwickTree(arr.size(), identity, merge) {
        for (int i = 0; i < n; i++)
            BIT[i + 1] = arr[i]; 
        for (int i = 1; i <= n; i++)
            if (int j = i + (i & -i); j <= n)
                BIT[j] = merge(BIT[j], BIT[i]);
    }

    void add(int idx, T delta) {
        for (idx++; idx <= n; idx += idx & -idx)
            BIT[idx] = merge(BIT[idx], delta);
    }

    T prefix(int idx) {
        T result = identity;
        for (idx++; idx > 0; idx -= idx & -idx)
            result = merge(result, BIT[idx]);
        return result;
    }
};