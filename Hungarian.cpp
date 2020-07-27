// Hungarian algorithm
// 
// Finds the minimum/maximum weight bipartite matching on a bipartite graph G(X, Y, E).
//
// Variables:
// - n is the number of vertices in X and Y
//
// Functions:
// - hungarian(a) returns maximum weight bipartite matching where a[i][j] is weight of edge (i, j)
//
// Note: for minimum weight multiply all elements of a by -1
//
// Time complexity: O(VE)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<ll, int>;

int n;

vector<int> hungarian(vector<vector<ll>>& a)
{
    constexpr ll inf = numeric_limits<ll>::max();
    vector<int> match(n + n, -1);
    for (int i = 0; i < n; ++i)
    {
        vector<ll> dst(n + n, inf), par(n + n, -1);
        dst[i] = 0;
        priority_queue<ii, vector<ii>, greater<ii>> pq;
        pq.emplace(dst[i], i);
        while (!pq.empty())
        {
            auto [c, x] = pq.top();
            pq.pop();
            if (c > dst[x]) continue;
            for (int j = 0; j < n; ++j)
            {
                if (match[i] == n + j) continue;
                int mj = match[n + j];
                ll nd = dst[x] + (mj == -1 ? -a[x][j] : -a[x][j] + a[mj][j]);
                if (mj == -1)
                {
                    if (nd < dst[n + j])
                    {
                        dst[n + j] = nd;
                        par[n + j] = x;
                    }
                }
                else if (nd < dst[mj])
                {
                    dst[mj] = nd;
                    par[mj] = x;
                    pq.emplace(nd, mj);
                }
            }
        }
        int x = n;
        for (int j = 0; j < n; ++j)
            if (dst[n + j] < dst[x])
                x = n + j;

        for (int y = par[x]; y != -1; y = par[y])
        {
            int z = match[y];
            match[y] = x;
            match[x] = y;
            x = z;
        }
    }
    return match;
}

int main()
{
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    vector<int> match = hungarian(a);
    ll cost = 0;
    for (int i = 0; i < n; ++i)
        cost += a[i][match[i] - n];
    cout << -cost << '\n';
    for (int i = 0; i < n; ++i)
        cout << match[i] - n << ' ';
}
