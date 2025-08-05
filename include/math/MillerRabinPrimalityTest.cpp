#include <bits/stdc++.h>
using namespace std;

/// Performs modular multiplication using __int128 to avoid overflow.
/// Returns (a * b) % m
#define _modmul(a, b, m) ((uint64_t)(((__int128_t)(a)*(b))%(m)))

/// Computes (x^y) % m using binary exponentiation.
uint64_t _modpow(uint64_t x, uint64_t y, uint64_t m) {
    uint64_t res = 1;
    while (y > 0) {
        if (y & 1) res = _modmul(res, x, m);
        x = _modmul(x, x, m);
        y >>= 1;
    }
    return res;
}

/// Deterministic Miller-Rabin primality test for 64-bit integers.
/// Returns true if n is prime, false otherwise.
bool prime_test(uint64_t n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    constexpr uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    uint64_t s = __builtin_clzll(n - 1), d = n >> s;
    for (auto a : bases) {
        uint64_t p = _modpow(a % n, d, n);
        uint64_t i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = _modmul(p, p, n);
        if (p != n - 1 && i != s) return false; 
    }
    return true;
}
