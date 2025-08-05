namespace strings {
    // z[i] = length of common prefix of s[0..n] and s[i..n]
    vector<i64> z_function(string const& s) {
        i32 n = s.size();
        vector<i32> z(n);
        i32 l = 0, r = 0;
        for (i32 i = 1; i < n; i++) {
            if (i < r) {
                z[i] = min(r - i, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }

    // Knuth-Morris-Pratt algorithm
    vector<int> prefix_function(string const& s) {
        int n = s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j])
                j = pi[j-1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }

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
            for(auto c: s) {
                t += string("#") + c;
            }
            auto res = manacher_odd(t + "#");
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


    // Rolling Hash
    struct StringHash {
        vector<i64> hash, power;
        const i64 P = 31;
        const i64 mod = 1e9 + 9;

        StringHash(const string& s) : hash(s.size() + 1, 0), power(s.size() + 1, 1) {
            for (i32 i = 0; i < sz(s); ++i) {
                hash[i + 1] = (hash[i] * P + s[i]) % mod;
                power[i + 1] = (power[i] * P) % mod;
            }
        }

        i64 substr(i32 l, i32 r) {
            return (hash[r + 1] - (hash[l] * power[r - l + 1] % mod) + mod) % mod;
        }
    };
} using namespace strings;