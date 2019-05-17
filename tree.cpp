#include <vector>
using namespace std;
using ll = long long;

const int MAX = 100000;
const int LG = 17;
ll length[MAX];
vector<int> adj[MAX];

int jump[MAX][LG];
int depth[MAX];
ll dist[MAX];

int tick;
int discovery[MAX];
int finish[MAX];

void dfs(int x, int p)
{
    jump[x][0] = (p == -1 ? x : p);
    for (int i = 1; i < LG; ++i)
        jump[x][i] = jump[jump[x][i - 1]][i - 1];

    discovery[x] = tick++;
    for (int y : adj[x])
    {
        if (y == p) continue;
        depth[y] = depth[x] + 1;
        dist[y] = dist[x] + length[y];
        dfs(y, x);
    }
    finish[x] = tick++;
}

bool is_ancestor(int x, int y)
{
    return discovery[x] <= discovery[y] && finish[y] <= finish[x];
}

int lca(int x, int y)
{
    if (is_ancestor(x, y)) return x;
    for (int i = LG-1; i >= 0; --i)
        if (!is_ancestor(jump[x][i], y))
            x = jump[x][i];
    return jump[x][0];
}

ll distance(int x, int y)
{
    return dist[x] + dist[y] - 2 * dist[lca(x, y)];
}

int num_edges(int x, int y)
{
    return depth[x] + depth[y] - 2 * depth[lca(x, y)];
}
