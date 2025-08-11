#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
istream& operator>>(istream& is, pair<K, V>& p) {
    return is >> p.first >> p.second;
}

template <typename C>
concept Container = requires(C c) {
    typename C::value_type;
    begin(c);
    end(c);
} and not same_as<remove_cvref_t<C>, string>;

template <Container C>
istream& operator>>(istream& is, C& c) {
    for (auto& x : c) 
        is >> x;
    return is;
}

template <Container C>
ostream& operator<<(ostream& os, const C& c) {
    for (auto const& x : c) 
        os << x << ' ';
    return os;
}
