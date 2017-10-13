// Articulation Points and Bridges
//
// Tarjan algorithm for finding articulation points and bridges.
//
// Variables:
// - G is the adjecency list of the graph.
// - N is the number of vertices in the graph.
// - articulation[x] is true if x is an articulation point.
// - discovery[x] is when vertex x is visited.
//
// Time complexity: O(V + E)
// 
// Note: This algorithm provides articulation points. To get the
// bridges you need to change 'if (w >= discovery[x])' to
// 'if (w > discovery[x])' then the edge (x, y) is an articulation
// bridge.

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

int tick, N;
vb articulation;
vi discovery;
vvi G; 

int dfs(int x, int dad)
{
	int low = discovery[x] = ++tick;
    int children = articulation[x] = 0;
    
	for (int y : G[x])
	{
		if (y == dad) 
			continue;
		if (discovery[y] < 0)
		{
			++children;
			int w = dfs(y, x);
			if (w >= discovery[x])
                articulation[x] = true;
			low = min(low, w);
		}
		else
			low = min(low, discovery[y]);
	}
	if (dad == -1) articulation[x] = children > 1;
	
	return low;
}

int main()
{
    G.assign(N, vi());
    discovery.assign(N, -1);
    articulation.assign(N, 0);
    tick = 1;
    for (int i = 0; i < N; ++i)
        if (discovery[i] == -1)
            dfs(i, -1);
}
