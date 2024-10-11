#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define int long long
// #define SINGLE_TEST_CASE
// #define FLOATING_POINT_IO
// #define INTERACTIVE_IO
// #define STRESS_TEST


namespace ultra {
    #define i32 long
    #define i64 long long
    #define all(v) begin(v),end(v)
    #define sz(v) (static_cast<int>((v).size()))

    constexpr i32 MAXN = 100'000;
    constexpr i64 MOD = 1'000'000'007;

    void solve();
    #define solve ultra::solve
} using namespace ultra;


signed main() {
    #ifdef STRESS_TEST
        test::generator();
    #else
        #ifndef INTERACTIVE_IO
            #define endl '\n'
            cin.tie(0)->sync_with_stdio(0);
        #endif
    #endif
    #ifdef FLOATING_POINT_IO
        #define double long double
        cout << fixed << setprecision(20);
    #endif
    #ifndef SINGLE_TEST_CASE
        i32 TC{1}; 
        cin >> TC;
        #ifdef STRESS_TEST
            bin >> TC;
        #endif 
        while (TC--)
    #endif
    {
        solve();
        #ifdef STRESS_TEST
            test::bruteforce();
        #endif
    }
    #ifdef STRESS_TEST
        test::validate();
    #endif
}


void solve() {
    int n; cin >> n;
    
}