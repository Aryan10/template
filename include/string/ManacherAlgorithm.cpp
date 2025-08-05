#include <bits/stdc++.h>
using namespace std;

// Manacher's algorithm, d[i] = diameter of palindrome centered at i
pair<vector<int>, vector<int>> manacher(string const& s) {
    auto manacher_odd = [] (string && s) -> vector<int> {
        int n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);
        int l = 1, r = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while(s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
    };

    auto manacher = [&] (string const& s) -> vector<int> {
        string t;
        for(char c : s)
            t += '#', t += c;
        auto res = manacher_odd(t + '#');
        return vector<int>(begin(res) + 1, end(res) - 1);
    };

    vector<int> v = manacher(s);
    int n = (v.size() + 1) / 2;
    vector<int> deven(n, 0), dodd(n, 0);
    for (int i = 0; i < v.size(); i++) {
        if (i % 2 == 0) dodd[i / 2] = v[i] - 1;
        else deven[(i+1) / 2] = v[i] - 1;
    }
    return {dodd, deven};
}