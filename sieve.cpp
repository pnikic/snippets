// Sieve of Eratosthenes
//
// Computes all primes less than a given bound
//
// Variables:
// - P is a list of all primes less than a given bound
// - maxn is the upper bound of primes
// - n is the number of primes less than the upper bound
// - maxN ~ number of primes less than maxn
//
// Functions:
// - SimpleSieve() stores all primes less than sqrt(maxn)
// - SegSieve() stores all primes less than maxn
//
// Time complexity: O(N(log(log N)))
// Space complexity:
// - O(N / log(N)) - if all primes are stored
// - O(sqrt(N)) - if only first sqrt(N) primes are stored

#include <iostream>
#include <cstring>
#include <ctgmath>

using namespace std;

typedef long long ll;

const ll maxN = 60000000;
const ll maxn = 100000000;
const ll fn = ll(sqrtl(maxn)) + 2;

ll Prime[fn], IsNotPrime[fn], p, n, P[maxN];

void SimpleSieve()
{
    for (ll i = 2; i < fn; ++i)
    {
        if (!IsNotPrime[i])
        {
            for (ll j = i * i; j < fn; j += i)
                IsNotPrime[j] = 1;

            P[n++] = Prime[p++] = i;
        }
    }
}

void SegSieve()
{
    SimpleSieve();
    ll lo = fn, hi = 2 * fn;
    while (lo < maxn)
    {
        if (hi >= maxn)
            hi = maxn;

        memset(IsNotPrime, 0, sizeof(IsNotPrime));
        for (ll i = 0; i < p; ++i)
        {
            int lolim = ll(lo / Prime[i]) * Prime[i];
            if (lolim < lo)
                lolim += Prime[i];

            for (ll j = lolim; j < hi; j += Prime[i])
                IsNotPrime[j - lo] = 1;
        }

        for (ll i = lo; i < hi; ++i)
            if (!IsNotPrime[i - lo])
                P[n++] = i;
                
        lo += fn, hi += fn;
    }
}
