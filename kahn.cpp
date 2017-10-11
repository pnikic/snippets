// Kahn's algorithm
//
// Gives a topological sorting on a DAG
//
// Variables
// - V, E are the number of vertices and edges of the graph
// - AdjList is the adjacency list of the graph
// - IND is a vector of in-degrees of the vertices 
//
// Time complexity: O(V + E)

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void kahn(vvi& AdjList, vi& IND)
{
    queue<int> Q;
    for (int i = 0; i < IND.size(); ++i)
		if (IND[i] == 0)
			Q.push(i);

    while (!Q.empty())
	{
		int x = Q.front(); Q.pop();
		// cout << x << " ";
		for (int y : AdjList[x])
			if (--IND[y] == 0)
				Q.push(y);
	}
}

int main()
{
	int V, E, u, v;
	cin >> V >> E;
	vvi AdjList(V);
	vi IND(V, 0);	//In degree
	for (int i = 0; i < E; ++i)
	{
		cin >> u >> v;
		AdjList[u].push_back(v);
		IND[v]++;
	}

    kahn(AdjList, IND);
}
