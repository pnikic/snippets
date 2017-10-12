// Euler Tour Algorithm 
//
// Checks whether a connected graph has an Euler Tour and prints it.
//
// Variables:
// - s is the start of the Euler Tour:
// - V, E are the number of vertices and edges in the graph.
// - cyc is the list of vertices in order of the Euler Tour.
// - G is the adjecency list of the graph.
// 
// Functions:
// - EulerTour(i, s) constructs an Euler Tour starting from vertex s.
// - HasEulerTour() checks whether the input graph contains an Euler Tour.
//
// Time complexity: O(E)

#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

int s, V, E;
vvii G;
list<int> cyc;

void EulerTour(list<int> :: iterator i, int u)
{
    for (int j = 0; j < G[u].size(); ++j)
    {
        ii v = G[u][j];
        if (v.second)
        {
            G[u][j].second = 0;
            for (int k = 0; k < G[v.first].size(); ++k)
            {
                ii uu = G[v.first][k];
                if (uu.first == u && uu.second)
                {
                    G[v.first][k].second = 0;
                    break;
                }
            }
            
            EulerTour(cyc.insert(i, u), v.first);
        }
    }
}

bool HasEulerTour()
{
    for (int u = 0; u < V; ++u)
        if (G[u].size() % 2)
            return false;

    return true;
}

int main()
{
    cin >> V >> E;
    G.assign(V, vii());
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v, 1);
        G[v].emplace_back(u, 1);
    }
    
    if (HasEulerTour())
    {
        cyc.clear();
        EulerTour(cyc.begin(), s);
        cout << s << '\n';
        for (auto p : cyc)
            cout << p << '\n';
    }
}
