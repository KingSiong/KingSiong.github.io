#include <bits/stdc++.h>
// #define debug

using namespace std;

enum Type {A, B};
const int MAX_N = 1e5 + 7;
vector<int> e[2][MAX_N];
int x[MAX_N], a[MAX_N], b[MAX_N]; 
bool cricial[MAX_N];
int siz[2][MAX_N], node[2][MAX_N], ans[2][MAX_N];
int n, k;
int lca;

void dfs(int u, Type type) {
    int cnt = cricial[u] ? 1 : 0;
    siz[type][u] = cricial[u] ? 1 : 0;
    node[type][u] = 0;
    for (auto v : e[type][u]) {
        dfs(v, type);
        siz[type][u] += siz[type][v];
        cnt += (siz[type][v] > 0);
        if (node[type][v]) node[type][u] = node[type][v];
    }
    if (cnt > 1 || cricial[u]) {
        lca = u;
    }
    if (cricial[u]) node[type][u] = u;
}

void solve(Type type) {
    dfs(1, type);
    for (int i = 1; i <= n; ++i) ans[type][i] = lca;
    if (cricial[lca]) {
        cricial[lca] = false;
        int tmp_lca = lca;
        dfs(1, type);
        ans[type][tmp_lca] = lca;
        cricial[tmp_lca] = true;
    } else {
        int cnt = 0;
        vector<int> son;
        for (auto v : e[type][lca]) {
            if (siz[type][v]) {
                ++cnt;
                if (siz[type][v] == 1) son.emplace_back(node[type][v]);
            }
        }
        if (cnt < 3) {
            for (auto v : son) {
                cricial[v] = false;
                dfs(1, type);
                ans[type][v] = lca;
                cricial[v] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= k; ++i) cin >> x[i], cricial[x[i]] = true;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        e[A][p].emplace_back(i);
    }
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        e[B][p].emplace_back(i);
    }
    solve(A); solve(B);
#ifdef debug
    cricial[3] = false;
    dfs(1, A);
    cout << lca << endl;
#endif
    int cnt = 0;
    for (int i = 1; i <= k; ++i) {
    #ifdef debug
        cout << ans[A][x[i]] << " " << x[i] << " " << ans[B][x[i]] << endl;
    #endif
        if (a[ans[A][x[i]]] > b[ans[B][x[i]]]) ++cnt;
    }
    cout << cnt << "\n";
    return 0;
}