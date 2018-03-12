// Binomial coefficient
// 
// Calculating nCr (n choose r).
//
// Variables:
// - mod is the module
// - maxn is the largest possible n
// - f[n] = n!
//
// Functions:
// - powmod(a, k) calculates a ^ k % mod
// - invmod(a) calculates inverse of a modulo mod
// - precompute() precomputes factorials up to maxn
// - nCr(n, r) calculates n choose r 
// 
// Time complexities:
// - powmod: O(log(k))
// - invmod: O(log(mod))
// - nCr: O(log(mod))
// - precompute: O(N)
//
// Note: before using nCr call precompute() to precompute factorials


#include <iostream>

using namespace std;

typedef long long ll;

const ll mod = 1000000009;
const ll maxn = 10000;

ll f[maxn];

ll powmod(ll a, ll k)
{
    ll res = 1;
    while (k)
    {
        if (k % 2)
            res = (res * a) % mod;
        
        a = (a * a) % mod;
        k /= 2;
    }

    return res;
}

ll invmod(ll a)
{
    return powmod(a, mod - 2);
}

ll nCr(ll n, ll r)
{
    return (f[n] * ((invmod(f[r]) * invmod(f[n - r])) % mod)) % mod;
}

void precompute()
{
    f[0] = 1;
    for (ll i = 1; i < maxn; ++i)
        f[i] = (i * f[i - 1]) % mod;
}
