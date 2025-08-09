#pragma GCC optimize("O3,unroll-loops")
#pragma region ultraaryan10
#include <bits/stdc++.h>
using namespace std;
#define int long long
// #define SINGLE_TEST_CASE
// #define FLOATING_POINT_IO
// #define INTERACTIVE_IO


#define all(v) std::begin(v), std::end(v)
#define len(v) (static_cast<int>((v).size()))

template<typename... Args> void print(Args&&... args) { ((cout << args << ' '), ...); }
template<typename... Args> void println(Args&&... args) { print(args..., '\n'); }
#ifndef ONLINE_JUDGE
template<typename... Args> void debug(Args&&... args) { ((cerr << args << ' '), ...); cerr << '\n'; }
#endif
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