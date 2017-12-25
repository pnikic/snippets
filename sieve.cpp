// Sieve of Eratosthenes
//
// Computes all primes less than a given bound
//
// Variables:
// - Primes is a list of all primes less than a given bound
// - IsPrime[x] is true if x is prime
// - maxn is the upper bound of primes
// - p is the number of primes less than the upper bound
//
// Functions:
// - Sieve(bound) stores all primes less than bound in Primes
//
// Time complexity: O(N(log(log N)))

#include <iostream>

using namespace std;

typedef long long ll;

const ll maxn = 100000;

ll Prime[maxn], IsPrime[maxn], p;

void Sieve()
{
    IsPrime[1] = IsPrime[1] = 1;

    for (ll i = 2; i < maxn; ++i)
    {
        if (!IsPrime[i])
        {
            for (ll j = i * i; j < maxn; j += i)
                IsPrime[j] = 1;

            Prime[p++] = i;
        }
    }
}

int main()
{
    Sieve();
}
