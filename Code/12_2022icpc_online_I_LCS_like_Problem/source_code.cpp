#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 7;
const int MAX_SIGMA = 27;
char s[MAX_N], t[MAX_N];
int dp[MAX_SIGMA], e[MAX_SIGMA][MAX_SIGMA];
bool vis[MAX_SIGMA];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin >> s >> t;
    n = strlen(s);
    m = strlen(t);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (vis[j]) {
                e[(int)(t[i] - 'a')][j] = true;
            }
        }
        vis[(int)(t[i] - 'a')] = true;
    }
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int ch = (int)(s[i] - 'a');
        if (!vis[ch]) {
            ++len;
            continue;
        }
        if (!e[ch][ch]) dp[ch] = max(dp[ch], dp[ch] + 1);
        for (int j = 0; j < 26; ++j) {
            if (j == ch) continue;
            if (!e[ch][j]) {
            #ifdef debug
                cout << (char)(ch + 'a') << "->" << (char)(j + 'a') << endl;
            #endif
                dp[ch] = max(dp[ch], dp[j] + 1);
            }
        }
    #ifdef debug
        cout << i << " " << dp[ch] << endl;
    #endif
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans + len << "\n";
    return 0;
}