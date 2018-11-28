// Fenwick Tree
//
// Dynamic data structure used to solve problems such as
// RSQ (Range Sum Queries) given a set of M integer keys that range
// from [1 ... N]. RangeFT allows range updates and queries in
// log N time.
//
// Functions:
// Class FenwickTree
// - rsq(a, b) returns the RSQ from a to b (inclusive).
// - adjust(N, v) add v to the Nth element.
// - q(N) returns Nth element.
// Class RangeFT
// - rsq(a, b) returns the RSQ from a to b (inclusive).
// - adjust(l, r, v) add v to elements from a to b (inclusive);
//
// Time complexities:
// - rsq: O(log N)
// - adjust: O(k log N)

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class FenwickTree
{
private:
    vector<T> ft;
public:
    FenwickTree () {}
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
};

template<class T>
class RangeFT
{
private:
    FenwickTree<T> mul, add;
public:
    RangeFT (int n) : mul(FenwickTree<T>(n)), add(FenwickTree<T>(n))
    {
    }
    T rsq(int a)
    {
        return mul.rsq(a) * a + add.rsq(a);
    }
    T rsq(int a, int b)
    {
        return rsq(b) - rsq(a - 1);
    }
    void adjust(int l, int r, T v)
    {
        mul.adjust(l, v);
        mul.adjust(r, -v);
        add.adjust(l, -v * (l - 1));
        add.adjust(r, v * r);
    }
};
