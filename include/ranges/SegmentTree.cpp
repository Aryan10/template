#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Merge = plus<void>>
struct SegmentTree {
    int n;
    vector<T> tree;
    T identity;
    function<T(T, T)> merge;

    SegmentTree(int n, T identity = T(), function<T(T, T)> merge = Merge()) 
        : n(n), identity(identity), merge(merge), tree(4 * n, identity) {}
    SegmentTree(vector<T> const& arr, T identity = T(), function<T(T, T)> merge = Merge()) 
        : SegmentTree(arr.size(), identity, merge) { 
        build(arr, 0, 0, n - 1);
    }

private:
    T const& build(vector<T> const& arr, int root, int l, int r) {
        if (l == r)
            return tree[root] = arr[l];
        int mid = l + (r - l) / 2;
        return tree[root] = merge(
            build(arr, 2 * root + 1, l, mid),
            build(arr, 2 * root + 2, mid + 1, r)
        );
    }

    T query(int root, int l, int r, int ql, int qr) const {
        if (ql <= l and r <= qr)
            return tree[root];
        if (r < ql or l > qr)
            return identity;
        int mid = l + (r - l) / 2;
        return merge(
            query(2 * root + 1, l, mid, ql, qr),
            query(2 * root + 2, mid + 1, r, ql, qr)
        );
    }
    
    T const& update(int root, int l, int r, int idx, T const& val) {
        if (l == r)
            return tree[root] = val;
        int mid = l + (r - l) / 2;
        if (idx <= mid)
            return tree[root] = merge(update(2 * root + 1, l, mid, idx, val), tree[2 * root + 2]);
        else
            return tree[root] = merge(tree[2 * root + 1], update(2 * root + 2, mid + 1, r, idx, val));
    }

public:
    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void update(int idx, T val) {
        update(0, 0, n - 1, idx, val);
    }
};