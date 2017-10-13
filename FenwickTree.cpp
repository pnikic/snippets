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

typedef vector<int> vi;

class FenwickTree
{
    private:
        vi ft;
    public:
        FenwickTree (int n)
        {
            ft.assign(n + 1, 0);
        }
        int rsq(int b)
        {
            int sum = 0;
            for (; b; b -= (b & (-b)))
                sum += ft[b];
            return sum;
        }
        int rsq(int a, int b)
        {
            return rsq(b) - ((a == 1)? 0 : rsq(a - 1));
        }
        void adjust(int k, int v)
        {
            for (; k < ft.size(); k += (k & (-k)))
                ft[k] += v;
        }
};
