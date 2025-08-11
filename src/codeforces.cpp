#pragma region ultraaryan10

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define int long long
// #define SINGLE_TEST_CASE
// #define FLOATING_POINT_IO
// #define INTERACTIVE_IO

/* MACRO */
#define all(v) std::begin(v), std::end(v)
#define len(v) (static_cast<int>((v).size()))

/* CONTAINERS & I/O */
template <typename T, typename CMP = less<void>>
using ordered_set = tree<T, null_type, CMP, rb_tree_tag, tree_order_statistics_node_update>;

template <typename K, typename V> istream& operator >> (istream& is, pair<K, V>& p) { return is >> p.first >> p.second; }
template <typename C> concept Container = requires(C c) { typename C::value_type; begin(c); end(c); } and not same_as<remove_cvref_t<C>, string>;
template <Container C> istream& operator>>(istream& is, C& c) { for (auto& x : c) is >> x; return is; }
template <Container C> ostream& operator<<(std::ostream& os, const C& c) { for (auto const& x : c) os << x << ' '; return os; }

/* PRINT & DEBUG */
template<typename... Args> void print(Args&&... args) { ((cout << args << ' '), ...); }
template<typename... Args> void println(Args&&... args) { ((cout << args << ' '), ...); cout << '\n'; }
#ifndef ONLINE_JUDGE
template<typename... Args> void debug(Args&&... args) { ((cerr << args << ' '), ...); cerr << '\n'; }
#endif

/* MAIN */
void solve();
signed main() {
    #ifndef INTERACTIVE_IO
        #define endl '\n'
        cin.tie(0)->sync_with_stdio(0);
    #endif
    #ifdef FLOATING_POINT_IO
        #define double long double
        cout << fixed << setprecision(20);
    #endif
    #ifndef SINGLE_TEST_CASE
        signed TC{1}; cin >> TC; while (TC--)
    #endif
        solve();
}
#pragma endregion



void solve() {
    
}