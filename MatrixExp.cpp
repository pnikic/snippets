// Matrix multiplication and exponentiation
//
// Fast matrix exponentiation and multiplication.
//
// Attributes:
// - dim is the dimension of the matrix.
// - A is the vector representing the matrix.
//
// Time complexities:
// - operator *: O(N ^ 3)
// - operator ^: O(N ^ 3 * log k)

#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Matrix
{
    vvi A;
    int dim;
    Matrix() {}
    Matrix(int n) : dim(n) { A.assign(n, vi(n));}
    vi &operator [](int n){ return A[n];}
};

Matrix operator *(Matrix A, Matrix B)
{
    int n = A.dim;
    Matrix C(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
       
    return C;
}

Matrix operator ^(Matrix A, int k)
{
    int n = A.dim;
    
    Matrix R(n);
    for (int i = 0; i < n; ++i)
        R[i][i] = 1;

    while (k > 0)
    {
        if (k % 2)
            R = R * A;

        A = A * A;
        k /= 2;
    }

    return R;
}

