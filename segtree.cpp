// Segment Tree
//
// Dynamic data structure used to answer dynamic range queries such as
// RSQ (Range Sum Query), RMQ (Range Minimum Query) and others.
// This implementation solves the RMQ problem given a set of N integers.
//
// Functions:
// - query(i, j) returns the RMQ on [i, j].
// - update(i, v) updates the i-th element to the value v.
//
// Time complexities:
// - build: O(N)
// - query: O(log N)
// - update: O(log N)
const int MAXN = 1 << 18; // 2.6e5
int N = 200000;
int seg[2 * MAXN]; // root is seg[1]

void build()
{
    for (int i = N - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void update(int p, int val)
{
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

int query(int l, int r) // [l, r]
{
    int res = 0;
    for (l += N, r += N; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res += seg[l++];
        if (!(r & 1))
            res += seg[r--];
    }
    return res;
}
