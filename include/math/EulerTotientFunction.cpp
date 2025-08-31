#include <bits/stdc++.h>
using namespace std;

/// Euler Totient Function using Sieve of Eratosthenes
/// phi(x) = no. of integers from 1 to x that are coprime with x
/// phi(x) = x * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk) where pi = prime factors of x
vector<int> EulerTotient(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {  // i is prime
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

/*

Multiplicativity: phi(ab) = phi(a) * phi(b) * g / phi(g) where g = gcd(a, b)

Divisor sum property: sigma [d|n] (phi(d)) = n

Euler's Theorem: If a and n are coprime, then a^(phi(n)) ≡ 1 (mod n)

*/