#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

namespace Blossom {
const int N = 1e3 + 10;
int n, m, cnt, fa[N], vis[N], pre[N], dfn[N], match[N], d[N], sum;
vector<int> G[N];
queue<int> q;
void ad(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int lca(int u, int v) {
    ++cnt;
    u = find(u), v = find(v);
    while (dfn[u] != cnt) {
        dfn[u] = cnt;
        u = find(pre[match[u]]);
        if (v) swap(u, v);
    }
    return u;
}
void blossom(int u, int v, int w) {
    while (find(u) != w) {
        pre[u] = v;
        v = match[u];
        if (vis[v] == 2) vis[v] = 1, q.push(v);
        if (find(u) == u) fa[u] = w;
        if (find(v) == v) fa[v] = w;
        u = pre[v];
    }
}
bool aug(int s) {
    for (int i = 1; i <= n; i++)
        fa[i] = i, vis[i] = pre[i] = 0;
    while (!q.empty())
        q.pop();
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : G[u]) {
            if (find(u) == find(v) || vis[v] == 2) continue;
            if (!vis[v]) {
                vis[v] = 2, pre[v] = u;
                if (!match[v]) {
                    for (int x = v, lst; x; x = lst)
                        lst = match[pre[x]], match[x] = pre[x], match[pre[x]] = x;
                    return true;
                }
                vis[match[v]] = 1, q.push(match[v]);
            } else {
                int w = lca(u, v);
                blossom(u, v, w);
                blossom(v, u, w);
            }
        }
    }
    return false;
}
int cal() {
    int res = 0;
    for (int i = 1; i <= n; i++)
        if (!match[i]) res += aug(i);
    return res;
} // 匹配数（ps:只有第一次调用有效

// 如果需要x的具体匹配: match[x]

// init(点个数)
void init(int t) {
    cnt = 0;
    n = t;
    for (int i = 1; i <= n; i++)
        G[i].clear(), match[i] = dfn[i] = 0;
}

} // namespace Blossom
// 1-indexed
 
void sol() { 
    int n,m;
    cin>>n>>m;
    Blossom::init(n);
    for(int i=0;i<m;++i)
    {
        int u,v;cin>>u>>v;
        Blossom::ad(u,v);
    }
    cout<<Blossom::cal()<<'\n';
    for(int i=1;i<=n;++i)
    cout<<Blossom::match[i]<<" \n"[i==n];
}
signed main() {
    int t = 1;
    // cin >> t;
    ios::sync_with_stdio(0), cin.tie(0);
    while (t--)
        sol();
    return 0;
}
