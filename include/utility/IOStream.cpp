#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V> istream& operator >> (istream& is, pair<K, V>& p) {
    return is >> p.first >> p.second;
}

template <typename T> istream& operator >> (istream& is, vector<T>& v) {
    for (T& i : v) is >> i;
    return is;
}

template <typename T> ostream& operator << (ostream& os, vector<T> const& v) {
    for (T const& i : v) os << i << " ";
    return os;
}