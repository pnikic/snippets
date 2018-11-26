// Segment Tree
//
// Dynamic data structure used to answer dynamic range queries such as
// RSQ (Range Sum Query), RMQ (Range Minimum Query) and others.
// This implementation solves the RMQ problem given a set of N integers.
//
// Functions:
// - rmq(i, j) returns the RMQ on [i, j].
// - update(i, v) updates the i-th element to the value v.
//
// Time complexities:
// - build: O(N)
// - rmq: O(log N)
// - update: O(log N)

#include <vector>
using namespace std;

typedef vector<int> vi;

class segtree
{
    vi& A;
    vi st;
    int n;
public:
    segtree(vi& A) : A(A), n(A.size())
    {
        st.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j)
    {
        return rmq(1, 0, n - 1, i, j);
    }

    void update(int i, int v)
    {
        A[i] = v;
        update(1, 0, n - 1, i);
    }

private:
    int left(int p)
    {
        return p << 1;
    }

    int right(int p)
    {
        return (p << 1) + 1;
    }

    void build(int p, int L, int R)
    {
        if (L == R)
            st[p] = L;
        else
        {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }

    int rmq(int p, int L, int R, int i, int j)
    {
        if (i > R || j < L) return -1;
        if (L >= i && R <= j) return st[p];

        int p1 = rmq(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return (A[p1] <= A[p2]) ? p1 : p2;
    }

    void update(int p, int L, int R, int i)
    {
        if (L == R) return;
        if (i <= (L + R) / 2)
            update(left(p), L, (L + R) / 2, i);
        else
            update(right(p), (L + R) / 2 + 1, R, i);

        st[p] = A[st[right(p)]] <= A[st[left(p)]] ? st[right(p)] : st[left(p)];
    }
};
