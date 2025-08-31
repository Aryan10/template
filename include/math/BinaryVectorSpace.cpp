#include <bits/stdc++.h>
using namespace std;

template <int N>
struct BinaryVectorSpace {
    int d = 0;
    array<int, N> basis{};

    void insert(int vector) {
        for (int i = 0; i < N; i++) {
            if ((vector & (1LL << i)) == 0) continue;
            if (basis[i]) vector ^= basis[i];
            else {
                basis[i] = vector;
                d++;
                break;
            }
        }
    }

    bool contains(int vector) const {
        for (int i = 0; i < N; i++) {
            if ((vector & (1LL << i)) == 0) continue;
            if (basis[i]) vector ^= basis[i];
            else return false;
        }
        return true;
    }

    int dimension() const {
        return d;
    }
};