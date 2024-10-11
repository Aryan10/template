namespace math {
    // precompute primes in O(nloglogn), query prime factors in O(logn)
    struct Sieve {
        vector<bool> isPrime;
        vector<i32> primes, spf;
        
        Sieve(i32 N) : isPrime(N, true), spf(N, 1) {
            isPrime[0] = isPrime[1] = false;
            spf[0] = 0;
            i32 i;
            for (i = 2; i * i < N; i++) {
                if (isPrime[i]) {
                    primes.push_back(i);
                    for (i32 j = i * i; j < N; j += i) {
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

        vector<i32> primeFactors(i32 x) {
            vector<i32> ret;
            while (x != 1 && spf[x] != 1) {
                ret.push_back(spf[x]);
                x /= spf[x];
            }
            if (x != 1) ret.push_back(x);
            return ret;
        }
    };

    // LCM of two integers
    i64 lcm(i64 a, i64 b) {
        return a * (b / gcd(a, b));
    }

    // python integer power function: power(x, y, m) = x^y (mod m)
    i64 power(i64 x, i64 y, i64 m = MOD) {
        i64 res = 1;
        while (y > 0) {
            if (y & 1)
                res = (res * x) % m;
            y = y >> 1;
            x = (x * x) % m;
        }
        return res % m;
    }
    
    // fermat's little theorem in MOD: modinv(Q, n, m) = Q^(-n) (mod m); m must be prime
    i64 modinv(i64 Q, i64 n, i64 m = MOD) {
        return power(Q, m - n - 1, m) % m;
    }

    // precompute factorials in MOD
    class Combinatorics {
        i64 maxn;
    public:
        vector<i64> factorial;
        vector<i64> inverse_factorial;

        Combinatorics(i64 maxn) : maxn(maxn), factorial(maxn), inverse_factorial(maxn) {
            factorial[0] = 1;
            inverse_factorial[0] = 1;
            for (i64 i = 1; i < maxn; ++i) {
                factorial[i] = (factorial[i - 1] * i) % MOD;
                inverse_factorial[i] = power(factorial[i], MOD - 2) % MOD;
            }
        }
        Combinatorics() : Combinatorics(MAXN+1) {};

        i64 nCr(i64 n, i64 r) {
            if (r > n || r < 0) return 0;
            i64 numerator = factorial[n] % MOD;
            i64 denominator = (inverse_factorial[r] * inverse_factorial[n-r]) % MOD;
            return (numerator * denominator) % MOD;
        }

        i64 nPr(i64 n, i64 r) {
            if (r > n || r < 0) return 0;
            i64 numerator = factorial[n] % MOD;
            i64 denominator = inverse_factorial[n-r] % MOD;
            return (numerator * denominator) % MOD;
        }
    };

    // deterministic Miller-Rabin primality test in O(logn)
    #define modmul(a, b, m) ((uint64_t)(((__int128_t)(a)*(b))%(m)))
    bool isPrime(uint64_t n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        uint64_t s = __builtin_clzll(n - 1), d = n >> s;
        for (auto a : bases) {
            uint64_t p = power(a % n, d, n);
            uint64_t i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = modmul(p, p, n);
            if (p != n - 1 && i != s) return false; 
        }
        return true;
    }
} using namespace math;