// Sieve of Eratosthenes
//
// Computes all primes less than a given bound
//
// Variables:
// - Primes is a list of all primes less than a given bound
// - IsPrime[x] is true if x is prime
// - bound is the upper bound of primes
//
// Functions:
// - Sieve(bound) stores all primes less than bound in Primes
//
// Time complexity: O(N(log(log N)))


#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

vll Primes, IsPrime;

void Sieve(ll bound)
{
    IsPrime.assign(bound, 1);
    IsPrime[0] = IsPrime[1] = 0;

    for (ll i = 2; i < bound; ++i)
    {
        if (IsPrime[i])
        {
            for (ll j = i * i; j < bound; j += i)
                IsPrime[j] = 0;

            Primes.push_back(i);
        }
    }
}

int main()
{
    ll bound;
    cin >> bound;
    Sieve(bound);
}
