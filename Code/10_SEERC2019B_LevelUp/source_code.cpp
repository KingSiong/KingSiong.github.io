#include <bits/stdc++.h>
#define int long long
#define debug

using namespace std;

struct Node {
    int x, t, y, r;
    bool operator < (const Node &u) {
        return x < u.x;
    }
};

const int INF = 1e18 + 7;
const int MAX_N = 5e2 + 7;
int dp[MAX_N << 1][MAX_N << 1];
Node a[MAX_N];
int n, s1, s2;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> s1 >> s2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].t
            >> a[i].y >> a[i].r;
    }
    sort(a + 1, a + n + 1);
    int M = 1000;
    for (int i = 0; i <= M; ++i) {
        for (int j = 0; j <= M; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = M; j >= 0; --j) {
            for (int k = M; k >= 0; --k) {
                if (j >= a[i].x && j - a[i].x < s1) {
                    dp[j][k] = min(dp[j][k], dp[j - a[i].x][k] + a[i].t);
                }
                if (k >= a[i].y) {
                    dp[j][k] = min(dp[j][k], dp[j][k - a[i].y] + a[i].r);
                }
            }
        }
    }
    int ans = INF;
    for (int i = s1; i <= M; ++i) {
        for (int j = max(0ll, s2 - i + s1); j <= M; ++j) {
            ans = min(ans, dp[i][j]);
        }
    }
    if (ans < INF) {
        cout << ans << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}