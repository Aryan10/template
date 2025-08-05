#include <bits/stdc++.h>
using namespace std;

int pow(int x, int y, int m) {
    while (y < 0) y += m - 1;
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % m;
        y >>= 1;
        x = 1LL * x * x % m;
    }
    return res;
}

class Combinatronics {
    int maxn, mod;
    
public:
    vector<int> factorial, inverse_factorial;
    Combinatronics(int maxn, int mod)
        : maxn(maxn), mod(mod), factorial(maxn + 1), inverse_factorial(maxn + 1) {
            factorial[0] = inverse_factorial[0] = 1;
            for (int i = 1; i <= maxn; ++i) {
                factorial[i] = 1LL * factorial[i - 1] * i % mod;
                inverse_factorial[i] = pow(factorial[i], -1, mod) % mod;
            }
        }

    int nCr(int n, int r) {
        if (r > n || r < 0) return 0;
        return 1LL * factorial[n] * inverse_factorial[r] % mod * inverse_factorial[n - r] % mod;
    }

    int nPr(int n, int r) {
        if (r > n || r < 0) return 0;
        return 1LL * factorial[n] * inverse_factorial[n - r] % mod;
    }

    /// Calculates the nth Catalan number
    /// Counts various combinatorial structures like balanced parentheses, binary trees, mountain ranges, etc.
    /// Formula: C_n = nCr(2n, n) / (n + 1)
    int catalan(int n) {
        return nCr(2 * n, n) * inverse_factorial[n + 1] % mod;
    }

    /// Calculates Stirling number of the second kind
    /// Counts the number of ways to partition a set of n labelled objects into k nonempty unlabelled subsets.
    /// Formula: {n k} = 1/k! * sum [i=0 to k] ( (-1)^(k-i) * nCr(k, i) * i^n )
    int stirling(int n, int k) {
        int s = 0;
        for (int i = 1; i <= k; i++) {
            int sign = (k - i) % 2 ? -1 : 1;
            s = ((s + sign * nCr(k, i) * pow(i, n, mod) % mod) % mod + mod) % mod;
        }
        return s * inverse_factorial[k] % mod;
    }
};