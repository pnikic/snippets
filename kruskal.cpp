// Kruskal's algorithm
//
// Finds a minimum spanning tree given a connected, undirected and weighted graph.
// It uses the lightweight Union-Find Disjoint Sets structure.
//
// Variables:
// - V, E are the number of vertices and edges of the graph
// - EdgeList is the list of edges (weight, vertex, vertex)
// - mst_cost is the sum of the weights of the selected edges
//
// Time complexity: O(E * logV)

#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

struct UF
{
    vi r, p;
    UF(int n) : r(n, 0), p(n, 0)
    {
        iota(p.begin(), p.end(), 0);
    }
	
    int f(int x)
    {
        return (p[x] == x ? x : p[x] = f(p[x]));
    }
	
    void u(int i, int j)
    {
        int x = f(i), y = f(j);
        if (x == y)
            return;

        if (r[x] >= r[y])
        {
            p[y] = x;
            if (r[x] == r[y])
                r[x]++;
        }
        else
            p[x] = y;
    }

    bool s(int i, int j)
    {
        return f(i) == f(j);
    }
};


void kruskal(viii& E, UF& uf, int& mst_cost)
{
    sort(E.begin(), E.end());
    for (auto& t : E)
    {
        int w, a, b;
        tie(w, a, b) = t;
        if (!uf.s(a, b))
            mst_cost += w, uf.u(a, b);
    }	
}

int main()
{
    int V, E, u, v, w;
    viii EdgeList;
    UF uf(V);

    for (int i = 0; i < E; ++i)
    {
        cin >> u >> v >> w;
        EdgeList.emplace_back(w, u, v);
    }
    
    int mst_cost = 0;
    kruskal(EdgeList, uf, mst_cost);
}
