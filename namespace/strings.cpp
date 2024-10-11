namespace strings {
    // z[i] = length of common prefix of s[0..n] and s[i..n]
    vector<i64> z_function(string const& s) {
        i64 n = s.size();
        vector<i64> z(n);
        i64 l = 0, r = 0;
        for (i64 i = 1; i < n; i++) {
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