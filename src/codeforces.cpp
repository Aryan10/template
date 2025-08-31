#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma region ultraaryan10
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, typename CMP = less<void>>
using ordered_set = tree<T, null_type, CMP, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long

/* MACRO */
#define endl '\n'
#define all(v) std::begin(v), std::end(v)
#define len(v) (static_cast<int>((v).size()))

/* I/O */
template <class C> concept Container = requires(C c) { typename C::value_type; begin(c); end(c); } and not same_as<remove_cvref_t<C>, string>;
template <Container C> istream& operator >> (istream& is, C& c) { for (auto& x : c) is >> x; return is; }
template <Container C> ostream& operator << (ostream& os, C const& c) { for (auto const& x : c) os << x << ' '; return os; }
template <class K, class V> istream& operator >> (istream& is, pair<K, V>& p) { return is >> p.first >> p.second; }
template <class K, class V> ostream& operator << (ostream& os, pair<K, V> const& p) { return os << p.first << ' ' << p.second << '\n'; }
template <class... Args> void print(Args&&... args) { ((cout << args << ' '), ...); }
template <class... Args> void println(Args&&... args) { ((cout << args << ' '), ...); cout << '\n'; }

#ifndef ONLINE_JUDGE
    #define DEBUG(x) cerr << #x << " = " << (x) << endl;
    template <class... Args> void debug(Args&&... args) { ((cerr << args << ' '), ...); cerr << '\n'; }
#endif

/* MAIN */
void solve();
bool __single_tc;
#define final auto __do_single = [] () { return __single_tc = true; } ();
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    signed TC{1}; 
    if (!__single_tc) cin >> TC; 
    while (TC--) solve();
}
#pragma endregion

void solve() {
    
}