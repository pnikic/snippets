// Sparse table
//
// Static data structure used to answer range queries such as RMQ
//
// Functions:
// - init(n) builds the sparse table
// - query(i, j) returns the RMQ on [i, j].
//
// Time complexities:
// - build: O(N log N)
// - query: O(1)
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100000;
const int maxl = 17;
int A[maxn], T[maxn][maxl];

void init(int n)
{
    for (int i = 0; i < n; ++i)
        T[i][0] = i;

    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 0; i + (1 << j) - 1 < n; ++i)
            T[i][j] = (A[T[i][j - 1]] < A[T[i + (1 << (j - 1))][j - 1]]) ?
                T[i][j - 1] : T[i + (1 << (j - 1))][j - 1];
}

int query(int i, int j)
{
    int k = 31 - __builtin_clz(j - i + 1);
    if (A[T[i][k]] <= A[T[j - (1 << k) + 1][k]])
        return T[i][k];
    else
        return T[j - (1 << k) + 1][k];
}

int main()
{
    init(maxn);
}
