// Topological Sort on DAG
//
// Prints out one topological sort for a given DAG (Directed Acyclic Graph).
//
// Variables:
// - G is the adjecency list of the graph.
// - P[x] is true if vertex x has been visited.
// - Sorted is the deque of topologicaly ordered vertices.
// - V, E are the number of vertices and edges in the graph.
// 
// Functions:
// - dfs(D, u) does a dfs from vertex u.
//
// Time complexity: O(E)

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi G;
vi P;

int dfs(deque<int> &D, int u)
{
    P[v] = 1;
    for (int v : G[u])
        if (!P[v])
            dfs(D, v);

    D.push_front(u);
}

int main()
{
    int V, E;
    G.assign(V, vi());
    cin >> V >> E;
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    deque<int> Sorted;
    P.assign(V, 0);
    for (int i = 0; i < V; ++i)
        if (!P[i])
            dfs(Sorted, i);
    
    for (int i : Sorted)
        cout << i << ' ';
}
