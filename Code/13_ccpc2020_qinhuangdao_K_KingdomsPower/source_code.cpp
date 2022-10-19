#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAX_N = 1e6 + 7;
vector<int> e[MAX_N];
int dp[MAX_N], dep[MAX_N], mx_dep[MAX_N];
int T, n;

void dfs(int u) {
    int cost = 1;
    mx_dep[u] = dep[u];
    int mx_cost = 1, sum_cost = 1;
    for (auto v : e[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        mx_dep[u] = max(mx_dep[u], mx_dep[v]);
        dp[u] += dp[v];
        cost = min(dep[u] + 1, mx_dep[v] - dep[u] + 1);
        mx_cost = max(mx_cost, cost);
        sum_cost += cost;
    }
    dp[u] += sum_cost - mx_cost;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> n;
        for (int i = 2; i <= n; ++i) {
            int fa;
            cin >> fa;
            e[fa].emplace_back(i);
        }
        dfs(1);
    #ifdef debug
        for (int i = 1; i <= n; ++i) {
            cout << i << ": " << dp[i] << endl;
        }
    #endif
        cout << "Case #" << cas << ": " << dp[1] << "\n";
        for (int i = 1; i <= n; ++i) dp[i] = dep[i] = mx_dep[i] = 0, e[i].clear();
    }
    return 0;
}