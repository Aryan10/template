#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(vector<int> const& arr) {
        n = arr.size();
        tree.resize(2 * n);
        build(arr);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < n; ++i)
            tree[n + i] = arr[i];
        for (int i = n - 1; i > 0; --i)
            tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int idx, int val) {
        idx += n;
        tree[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (!(r & 1)) res = max(res, tree[r--]);
        }
        return res;
    }
};