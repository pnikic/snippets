#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

vvi G, T;
vb B;
stack<int> S;

void dfs(int x)
{
    B[x] = true;
    for (int y : G[x])
        if (!B[y])
            dfs(y);
    S.push(x);
}

void dfs2(int x)
{
    B[x] = true;
    cout << x + 1 << ' ';
    for (int y : T[x])
        if (!B[y])
            dfs2(y);
}

int main()
{
    int n, m;
    cin >> n >> m;
    G.resize(n);
    T.resize(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        T[v].push_back(u);
    }
    B.resize(n);
    for (int i = 0; i < n; ++i)
        if (!B[i])
            dfs(i);

    fill(B.begin(), B.end(), false);
    while (!S.empty())
    {
        if (!B[S.top()])
        {
            dfs2(S.top());
            cout << endl;
        }
        S.pop();
    }
}
