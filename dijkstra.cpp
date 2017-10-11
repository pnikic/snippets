// Dijkstra's algorithm
//
// Calculates SSSP (single source shortest path) on a weighted graph.
//
// Variables:
// - V, E are the number of vertices and edges of the graph
// - s is the source
// - AdjList is the adjacency list of the graph
// - dist is the vector of distances from the vertices to the source
//
// Time complexity: O((V + E)logV)

#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
#define INF 1000000000

void dijkstra(vvii& AdjList, vi& dist, int s)
{
    priority_queue<ii, vii, greater<ii> > pq;
    pq.emplace(0,s);

    while (!pq.empty())
    {
        int d, u;
        tie(d, u) = pq.top(); pq.pop();

        if (d > dist[u])
            continue;
        
        for (ii v : AdjList[u])
        {
            if (dist[u] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u] + v.second;
                pq.emplace(dist[v.first], v.first);
            }
        }
    }
}

int main()
{
    int V, E, s, u, v, w;
    vvii AdjList;
    cin >> V >> E >> s;

    AdjList.assign(V, vii());
    for (int i = 0; i < E; ++i)
    {
        cin >> u >> v >> w;
        AdjList[u].emplace_back(v, w);     // directed graph
        //AdjList[v].emplace_back(u, w);
    }

    vi dist(V, INF); dist[s] = 0;
    dijkstra(AdjList, dist, s);
}
