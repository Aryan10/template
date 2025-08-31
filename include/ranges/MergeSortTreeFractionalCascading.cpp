#include <bits/stdc++.h>
using namespace std;

/// Merge sort tree with fractional cascading
/// Query array[l, r] for no. of elements in range [c, d] in O(log n)
struct MergeSortTree {
    struct MSTNode { 
        vector<int> vals, L, R;

        void init(int val) {
            vals = {val}, L = {0, 1}, R = {0, 1};
        }

        void resize(int sz) {
            vals.reserve(sz);
            L.resize(sz + 1, 0);
            R.resize(sz + 1, 0);
        }
    };

    size_t n, base;
    vector<MSTNode> tree;
    MergeSortTree(vector<int> &a) : n(a.size()), base(bit_ceil(n)), tree(2 * base) {        
        for (int i = 0; i < n; ++i)
            tree[base + i].init(a[i]);

        for (int i = base - 1; i > 0; i--) {
            auto &left = tree[i << 1].vals, &right = tree[i << 1 | 1].vals;

            tree[i].resize(left.size() + right.size());
            
            int li = 0, ri = 0, lcnt = 0, rcnt = 0;

            for (int k = 0; k < left.size() + right.size(); k++) {
                if (ri == right.size() or (li < left.size() and left[li] <= right[ri])) {
                    tree[i].vals.push_back(left[li++]);
                    ++lcnt;
                } else {
                    tree[i].vals.push_back(right[ri++]);
                    ++rcnt;
                }
                tree[i].L[k + 1] = lcnt;
                tree[i].R[k + 1] = rcnt;
            }
        }
    }

    int query(int l, int r, int c, int d) {
        if (l > r) return 0;
        int lo = lower_bound(tree[1].vals.begin(), tree[1].vals.end(), c) - tree[1].vals.begin();
        int hi = upper_bound(tree[1].vals.begin(), tree[1].vals.end(), d) - tree[1].vals.begin();
        return query(1, 0, base - 1, l, r, lo, hi);
    }

private:
    int query(int root, int l, int r, int ql, int qr, int low, int high) {
        if (l > qr || r < ql || low >= high) return 0;
        if (ql <= l && r <= qr) return high - low;
        int mid = (l + r) >> 1, left = root << 1, right = left | 1;
        auto &L = tree[root].L, &R = tree[root].R;
        return query(left, l, mid, ql, qr, L[low], L[high]) + query(right, mid + 1, r, ql, qr, R[low], R[high]);
    }
};