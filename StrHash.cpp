#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 9;
int add(int a, int b) { return (a += b) < mod? a : a - mod; }
int sub(int a, int b) { return (a -= b) >=  0? a : a + mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pwr(int a, int p) {
    if (p == 0) return 1;
    if (p & 1) return mul(a, pwr(a, p - 1));
    return pwr(mul(a, a), p / 2);
}
int inv(int a) { return pwr(a, mod - 2); }

const int maxn = 100000;
int invp[maxn], ppow[maxn], pref[maxn + 1];

void pre_hash(const string& s)
{
    for (int i = 0; i < s.size(); ++i)
        pref[i + 1] = add(pref[i], mul(s[i] - 'a' + 1, ppow[i]));
}

int substr_hash(int i, int j)
{
    return mul(invp[i], sub(pref[j + 1], pref[i]));
}

int hash_f(const string& s)
{
    ll p = 1, h = 0;
    for (int i = 0; i < s.size(); ++i)
        h = add(h, mul(s[i] - 'a' + 1, ppow[i]));
    return h;
}

vector<int> rabin_karp(string const& s, string const& t)
{
    pre_hash(t);
    ll h_s = hash_f(s);
    vector<int> occurences;
    for (int i = 0; i + s.size() - 1 < t.size(); i++)
        if (substr_hash(i, i + s.size() - 1) == h_s)
            occurences.push_back(i);
    return occurences;
}

int LCP(const string& s, int x0, int y0, int x1, int y1)
{
    if (s[x0] != s[x1])
        return 0;

    int lo = 1, hi = min(y0 - x0 + 1, y1 - x1 + 1);
    while (lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if (substr_hash(x0, x0 + mid - 1) == substr_hash(x1, x1 + mid - 1))
            lo = mid;
        else
            hi = mid-1;
    }
    return lo;
}

bool cmp(const string& s, int x0, int y0, int x1, int y1)
{
    int L = LCP(s, x0, y0, x1, y1);
    if (L == y0 - x0 + 1) return true;
    if (L == y1 - x1 + 1) return false;
    return s[x0 + L] < s[x1 + L];
}

int main()
{
    invp[0] = ppow[0] = 1;
    for (int i = 1; i < maxn; ++i)
    {
        ppow[i] = mul(ppow[i - 1], 31);
        invp[i] = inv(ppow[i]);
    }

    string s = "mislav";
    string z = "isla";
    pre_hash(s);
    cout << hash_f(z) << ' ' << substr_hash(1, 4) << endl;
    for (int x : rabin_karp("la", "lahhlllallarla"))
        cout << x << ' ';
}
