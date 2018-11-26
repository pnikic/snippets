// Fenwick Tree
//
// Dynamic data structure used to solve problems such as
// RSQ (Range Sum Queries) given a set of M integer keys that range
// from [1 ... N].
//
// Functions:
// - rsq() returns the RSQ.
// - adjust(k, N) update.
//
// Time complexities:
// - rsq: O(log N)
// - adjust: O(k log N)

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template <class T>
class FenwickTree
{
private:
    vector<T> ft;
public:
    FenwickTree (int n) : ft(n + 1)
    {
    }
    T rsq(int b)
    {
        T sum = 0;
        for (; b; b -= (b & (-b)))
            sum += ft[b];
        return sum;
    }
    T rsq(int a, int b)
    {
        return rsq(b) - rsq(a);
    }
    T q(int x)
    {
        return rsq(x) - rsq(x - 1);
    }
    void adjust(int k, T v)
    {
        for (; k < ft.size(); k += (k & (-k)))
            ft[k] += v;
    }
    void adjust(int l, int r, T v)
    {
        adjust(l, v);
        adjust(r + 1, -v);
    }
};
