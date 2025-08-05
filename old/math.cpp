namespace math {
    // precompute primes in O(nloglogn), query prime factors in O(logn)
    struct Sieve {
        vector<bool> isPrime;
        vector<int> primes, spf;
        
        Sieve(int N) : isPrime(N, true), spf(N, 1) {
            isPrime[0] = isPrime[1] = false;
            spf[0] = 0;
            int i;
            for (i = 2; i * i < N; i++) {
                if (isPrime[i]) {
                    primes.push_back(i);
                    for (int j = i * i; j < N; j += i) {
                        isPrime[j] = false;
                        if (spf[j] == 1) spf[j] = i;
                    }
                }
            }
            for (; i < N; i++) {
                if (isPrime[i]) primes.push_back(i);
            }
        }
        Sieve() : Sieve(MAXN+1) {}

        vector<int> primeFactors(int x) {
            vector<int> ret;
            while (x != 1 && spf[x] != 1) {
                ret.push_back(spf[x]);
                x /= spf[x];
            }
            if (x != 1) ret.push_back(x);
            return ret;
        }

        int divisorCount(int x) {
            map<int, int> pf;
            for (int i : primeFactors(x))
                pf[i]++;
            int ret = 1;
            for (auto [p, c] : pf)
                ret *= c + 1;
            return ret;
        }
    };

    // LCM of two integers
    int lcm(int a, int b) {
        return a * (b / gcd(a, b));
    }

    // python integer power function: power(x, y, m) = x^y (mod m)
    int power(int x, int y, int m = MOD) {
        int res = 1;
        while (y > 0) {
            if (y & 1)
                res = (res * x) % m;
            y = y >> 1;
            x = (x * x) % m;
        }
        return res % m;
    }

    int discretelog(int a, int b, int m = MOD) {
        a %= m, b %= m;
        int n = sqrt(m) + 1;

        int an = 1;
        for (int i = 0; i < n; ++i)
            an = (an * 1ll * a) % m;

        unordered_map<int, int> vals;
        for (int q = 0, cur = b; q <= n; ++q) {
            vals[cur] = q;
            cur = (cur * 1ll * a) % m;
        }

        for (int p = 1, cur = 1; p <= n; ++p) {
            cur = (cur * 1ll * an) % m;
            if (vals.count(cur)) {
                int ans = n * p - vals[cur];
                return ans;
            }
        }
        return -1;
    }
    
    // fermat's little theorem in MOD: modinv(Q, n, m) = Q^(-n) (mod m)
    int modinv(int Q, int n = 1, int m = MOD) {
        return power(Q, m - n - 1, m) % m;
    }

    // precompute factorials in MOD
    class Combinatorics {
        int maxn;
    public:
        vector<int> factorial;
        vector<int> inverse_factorial;

        Combinatorics(int maxn) : maxn(maxn), factorial(maxn), inverse_factorial(maxn) {
            factorial[0] = 1;
            inverse_factorial[0] = 1;
            for (int i = 1; i < maxn; ++i) {
                factorial[i] = (factorial[i - 1] * i) % MOD;
                inverse_factorial[i] = power(factorial[i], MOD - 2) % MOD;
            }
        }
        Combinatorics() : Combinatorics(MAXN+1) {};

        // nCr(n, r) = n! / (r! * (n - r)!)
        int nCr(int n, int r) {
            if (r > n || r < 0) return 0;
            int numerator = factorial[n] % MOD;
            int denominator = (inverse_factorial[r] * inverse_factorial[n-r]) % MOD;
            return (numerator * denominator) % MOD;
        }

        // nPr(n, r) = n! / (n - r)!
        int nPr(int n, int r) {
            if (r > n || r < 0) return 0;
            int numerator = factorial[n] % MOD;
            int denominator = inverse_factorial[n-r] % MOD;
            return (numerator * denominator) % MOD;
        }

        // Stirling number of the second kind
        // counts the number of ways to partition a set of n labelled objects into k nonempty unlabelled subsets.
        // {n k} = 1/k! * sigma[0-k]( (-1)^(k-i) * nCr(k, i) * i^n) )
        int stirling(int n, int k) {
            int s = 0;
            for (int i = 1; i <= k; i++) {
                s = (((s + ( ((k - i) % 2) ? -1 : 1) * nCr(k, i) * power(i, n)) + MOD) % MOD + MOD) % MOD;
            }
            return s * inverse_factorial[k] % MOD;
        }

        // Catalan number
        // C_n = nCr(2n, n) / (n + 1)
        int catalan(int n) {
            int numerator = factorial[2*n] % MOD;
            int denominator = inverse_factorial[n] * inverse_factorial[n+1] % MOD;
            return numerator * denominator % MOD;
        }
    };

    // deterministic Miller-Rabin primality test in O(logn)
    #define _modmul(a, b, m) ((uint64_t)(((__int128_t)(a)*(b))%(m)))
    bool isPrime(uint64_t n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        uint64_t s = __builtin_clzll(n - 1), d = n >> s;
        for (auto a : bases) {
            uint64_t p = power(a % n, d, n);
            uint64_t i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = _modmul(p, p, n);
            if (p != n - 1 && i != s) return false; 
        }
        return true;
    }

    namespace matrix {
        template <typename Matrix>
        consteval Matrix identity() {
            Matrix res{};
            for (int i = 0; i < res.size(); i++)
                res[i][i] = 1;
            return res;
        }

        template <typename Matrix>
        Matrix multiply(Matrix a, Matrix b, int mod = MOD) {
            Matrix res{};
            int n = a.size();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
                    }
                }
            }
            return res;
        }

        template <typename Matrix>
        Matrix power(Matrix a, int p, int mod = MOD) {
            Matrix res = identity<Matrix>();
            while (p > 0) {
                if (p & 1) res = multiply(res, a, mod);
                a = multiply(a, a, mod);
                p >>= 1;
            }
            return res;
        }
    };
} using namespace math;