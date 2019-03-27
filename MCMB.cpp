// Augmenting path algorithm
// 
// Finds the maximum cardinality bipartite matching on a bipartite graph G(X, Y, E).
//
// Variables:
// - G is the adjecency list of the graph.
// - n and m are the numbers of vertices in the sets X and Y.
// - M is the list of matches vertices.
// - MCBM is the number of matched pairs in a maximum cardinality bipartite matching.
//
// Functions:
// - Aug(u) finds an augmenting path starting from the vertex u.
//
// Note: The bipartite graph is directed from set X to set Y. If you start with an
// undirected graph, the real MCBM will be half of the obtained value by the
// algorithm. The vertices in X are numbered from [0 ... n - 1] and the
// vertices in Y are numbered from [n ... m - 1]. 
// 
// Time complexity: O(V * E)

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int n, m, tick;
vi V, M;
vvi G;

int Aug(int u)
{
    if (V[u] == tick)
        return 0;

    V[u] = tick;
    for (int v : G[u])
        if (M[v] == -1 || Aug(M[v]))
            return M[v] = u, 1;
            
    return 0;
}

int main()
{
    G.assign(n + m, vi());
    M.assign(n + m, -1);
    V.assign(n, 0);
    int MCBM = 0;
    for (int i = 0; i < n; ++i)
        ++tick, MCBM += Aug(i);
}
