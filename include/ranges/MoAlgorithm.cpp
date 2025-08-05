#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MoAlgorithm {
    struct Struct {
        virtual void add(int) = 0;
        virtual void remove(int) = 0;
        virtual T query(void) = 0;
    };
    
    struct Query {
        int l, r, idx, block;

        Query(int l, int r, int idx, int block_size)
            : l(l), r(r), idx(idx), block(l / block_size) {}

        bool operator<(const Query& other) const {
            if (block != other.block) return block < other.block;
            return (block & 1) ? r > other.r : r < other.r;
        }
    };

    const int block_size;
    vector<Query> queries;
    Struct& ds;

    MoAlgorithm(int n, Struct& ds) : block_size((int)sqrt(n) + 1), ds(ds) {}

    void push_query(int l, int r) {
        queries.emplace_back(l, r, queries.size(), block_size);
    }

    vector<T> operator () () {
        vector<T> answer(queries.size());
        sort(queries.begin(), queries.end());

        int cur_l = 0, cur_r = -1;
        for (auto const& q : queries) {
            while (cur_l > q.l) ds.add(--cur_l);
            while (cur_r < q.r) ds.add(++cur_r);
            while (cur_l < q.l) ds.remove(cur_l++);
            while (cur_r > q.r) ds.remove(cur_r--);
            answer[q.idx] = ds.query();
        }

        return answer;
    }
};