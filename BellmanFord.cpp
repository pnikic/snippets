// Bellman Ford's algorithm
//
// Calculates SSSP (single source shortest path) on a weighted graph and
// detects if a graph contains a negative cycle.
//
// Variables:
// - G is the edge list of the graph.
// - s is the source.
// - dist is the vector of distances from the source to other vertices.
// - V, E are the number of vertices and edges of the graph.
//
// Functions:
// - BellmanFord() stores lengths of shortest paths in dist and returns true
// if there exists a negative weight cycle.
//
// Time complexity: O(VE)

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

#define inf 1e9

typedef tuple<int, int, int> iii;
typedef vector<iii> viii;
typedef vector<int> vi;

int s, V, E;
viii G;
vi dist;

bool BellmanFord()
{
    dist.assign(V, inf);
    dist[s] = 0;
    int u, v, w;
    for (int i = 0; i < V - 1; ++i)
        for (iii e : G)
            tie(u, v, w) = e, dist[v] = min(dist[v], dist[u] + w);
       
    for (iii e : G)
    {
        tie(u, v, w) = e;
        if (dist[v] > dist[u] + w)
            return true;
    }
    
    return false;
}

int main()
{
    G.clear();
    cin >> V >> E;
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G.emplace_back(u, v, w);
    }
    
    BellmanFord();
}
