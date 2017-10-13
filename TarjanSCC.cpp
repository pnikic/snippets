// Tarjan Algorithm for SCC
//
// Finds SCC(Strongly Connected Components)
//
// Variables:
// - G is the adjecency list of the graph.
// - V is the number of vertices in the graph.
// - discovery[x] is true if x has been visited.
// - SCC is the number of strongly connected components.
// - S is a temporary "stack" (vector) that holds the current SCC.
//
// Time complexity: O(V + E)

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi G;
vi discovery, num, low, S;
int SCC, tick, V;

void tarjan(int u)
{
    low[u] = num[u] = tick++;
    S.push_back(u);
    discovery[u] = 1;
    for (int v : G[u])
    {
        if (num[v] == -1)
            tarjan(v);
        
        if (discovery[v])
            low[u] = min(low[u], low[v]);
    }
    
    if (low[u] == num[u])
    {
        SCC++;
        while (true)
        {
            int v = S.back(); S.pop_back(); discovery[v] = 0;
            // cout << v << '\n';
            if (u == v)
                break;
        }
    }
}

int main()
{
    G.assign(V, vi());
    SCC = tick = 0;
    num.assign(V, -1);
    low.assign(V, 0);
    discovery.assign(V, 0);
    for (int i = 0; i < V; ++i)
        if (num[i] == -1)
            tarjan(i);
}
