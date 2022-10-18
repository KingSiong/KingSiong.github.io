/*

注意状態不能設為 f[i][k]，k 是當前操作了幾次，而是注意到每次都能删兩个數，所以 k 是删了幾個數，答案為 f[n][2,4,\ldots,n * 2].

*/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAX_N = 1e2 + 7;
int dp[MAX_N][MAX_N << 1], a[MAX_N];
int n;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) {
        for (int k = 0; k <= n * 2; ++k) {
            for (int j = 1; j < i; ++j) {
                int c = i - j - 1;
                if (k >= c) {
                    dp[i][k] = max(dp[i][k], dp[j][k - c] + (a[j] - a[i]) * (a[j] - a[i]));
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) cout << dp[n][i * 2] << "\n";
    return 0;
}