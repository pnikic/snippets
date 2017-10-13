// Prim's algorithm
//
// Computes the maximum spanning tree and solves the maximin problem.
// If the minimum spanning tree is needed, you should use
// priority_queue<ii, vector<ii>, greater<ii> > instead.
//
// Variables:
// - G is the adjacency list of the graph
// - Q is max PQ containing the graph edges
// - root is the root of the MST
// - T is a vector that indicates if a vertex is taken in the tree
// - maximin will contain the minimum weighted edge in the maximum spanning tree
//
// Time complexity: O(E * logV)

#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef priority_queue<ii> pqii;
typedef vector<bool> vb;

void p(pqii& Q, vvii& G, vb& T, int x)
{
    T[x] = true;
    for (ii s : G[x])
        if (!T[s.second])
            Q.push(s);
}

int main()
{
    vvii G;
    // ...
    int root, maximin = numeric_limits<int>::max();
    pqii Q;
    vb T(G.size());
    p(Q, G, T, root);

    int mst_cost = 0;
    while (!Q.empty())
    {
        int w, x;
        tie(w, x) = Q.top(); Q.pop();
        if (!T[x])
            maximin = min(maximin, w), p(Q, G, T, x);
	}
}
