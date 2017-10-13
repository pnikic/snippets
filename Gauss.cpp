// Gaussian Elimination
//
// Solves system of linear equations Ax = b.
//
// Variables:
// - N dimension of the system.
// - A is the augmented matrix (A = [A, b]).
// 
// Time complexity: O(N ^ 3)

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<double> vd;
typedef vector<vd> vvd;

vd GaussianElimination(int N, vvd& A)
{
    double t;
    vd X(N);
    for (int j = 0; j < N - 1; ++j)
    {
        int l = j;
        for (int i = j + 1; i < N; ++i)
            if (fabs(A[i][j]) > fabs(A[l][j]))
                l = i;

        for (int k = j; k <= N; ++k)
            t = A[j][k], A[j][k] = A[l][k], A[l][k] = t;

        for (int i = j + 1; i < N; ++i)
            for (int k = N; k>= j; --k)
                A[i][k] -= A[j][k] * A[i][j] / A[j][j];
    }

    for (int j = N - 1; j >= 0; --j)
    {
        t = 0;
        for (int k = j + 1; k < N; ++k)
            t += A[j][k] * X[k];

        X[j] = (A[j][N] - t) / A[j][j];
    }

    return X;
}

int main()
{
    int n;
    cin >> n;
    vvd A(n, vd(n + 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            cin >> A[i][j];

    vd X = GaussianElimination(n, A);
    for (int i = 0; i < n; ++i)
        cout << X[i] << endl;
}
