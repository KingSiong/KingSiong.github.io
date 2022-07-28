#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Node {
    int v, e, p;
};

typedef pair<int, int> pii;
const int MAX_N = 1e5 + 7;
const int INF = 1e18;
vector<Node> edge[MAX_N], new_edge[MAX_N], E[MAX_N];
int dis[MAX_N], fitness[MAX_N], deg[MAX_N];
bool vis[MAX_N];
int T, n, m;
int dfn[MAX_N], low[MAX_N], scc[MAX_N];
bool in_st[MAX_N];
int order, num;
stack<int> st;

void tarjan(int u) {
    dfn[u] = low[u] = ++order;
    st.push(u);
    in_st[u] = true;
    for (auto item : new_edge[u]) {
        int v = item.v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_st[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int tmp;
        num++;
        do {
            tmp = st.top(); 
            st.pop();
            scc[tmp] = num;
            in_st[tmp] = false;
        } while(tmp != u);
    }
}


void dijkstra() {
    priority_queue<pii> q;
    for (int i = 0; i <= n; ++i) dis[i] = INF, fitness[i] = 0, vis[i] = false, deg[i] = 0;
    dis[1] = fitness[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty()) {
        pii p = q.top(); q.pop();
        int u = p.second;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto item : edge[u]) {
            int v = item.v, e = item.e;
            if (dis[v] > dis[u] + e) {
                dis[v] = dis[u] + e;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
    for (int u = 1; u <= n; ++u) {
        for (auto item : edge[u]) {
            int v = item.v, e = item.e, p = item.p;
            if (dis[u] + e == dis[v]) {
                new_edge[u].push_back({v, e, p});
            }
        }
    }
    for (int i = 0; i <= n; ++i) dfn[i] = low[i] = scc[i] = 0, E[i].clear(), in_st[i] = false;
    num = order = 0;
    while (!st.empty()) st.pop();
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; ++i) {
        for (auto item : new_edge[i]) {
            int v = item.v, e = item.e, p = item.p;
            if (scc[i] == scc[v]) continue;
            E[scc[i]].push_back({scc[v], e, p});
            ++deg[scc[v]];
        }
    }
    queue<int> topo;
    topo.push(scc[1]);
    while (!topo.empty()) {
        int u = topo.front(); topo.pop();
        for (auto item : E[u]) {
            int v = item.v, p = item.p;
            fitness[v] = max(fitness[v], fitness[u] + p);
            --deg[v];
            if (!deg[v]) topo.push(v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            int u, v, e, p;
            cin >> u >> v >> e >> p;
            edge[u].push_back({v, e, p});
        }
        dijkstra();
        cout << dis[n] << " " << fitness[scc[n]] << "\n";
        for (int i = 1; i <= n; ++i) edge[i].clear(), new_edge[i].clear();
    }
    return 0;
}