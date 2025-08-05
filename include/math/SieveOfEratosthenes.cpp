#include <bits/stdc++.h>
using namespace std;

struct Sieve {
    int N;
    vector<int> spf;
    
    Sieve(int N) : N(N), spf(N + 1, 0) {
        spf[0] = spf[1] = true;
        for (int i = 2; i <= N; i++) {
            if (spf[i]) continue;
            for (int j = i * i; j <= N; j += i) {
                if (spf[j]) continue;
                spf[j] = i;
            }
        }
    }

    bool isPrime(int x) {
        return not spf[x];
    }

    vector<int> getPrimes() {
        vector<int> primes;
        for (int i = 2; i <= N; i++)
            if (not spf[i]) primes.push_back(i);
        return primes;
    }

    unordered_map<int, int> getPrimeFactors(int x) {
        unordered_map<int, int> primeFactors;
        while (spf[x] > 1) {
            primeFactors[spf[x]]++;
            x /= spf[x];
        }
        primeFactors[x]++;
        return primeFactors;
    } 

    int getDivisorCount(int x) {
        auto primeFactors = getPrimeFactors(x);
        int divisorCount = 1;
        for (auto [prime, exponent] : primeFactors)
            divisorCount *= (exponent + 1);
        return divisorCount;
    }
};