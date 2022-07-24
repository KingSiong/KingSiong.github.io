#include <bits/stdc++.h>
#define int long long
#define debug

using namespace std;

typedef pair<double, int> pdi;
const int MAX_N = 5e5 + 7;
const double EPS = 1e-9;
int a[MAX_N], g[MAX_N]; 
double dp[MAX_N];
int n, k;

pdi get_k(double r) {
    for (int i = 0; i < n; ++i) dp[i] = g[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 1) {
            if (dp[i - 1] > dp[i - 2] + a[i] - r) {
                dp[i] = dp[i - 1];
                g[i] = g[i - 1];
            } else if (dp[i - 1] < dp[i - 2] + a[i] - r) {
                dp[i] = dp[i - 2] + a[i] - r;
                g[i] = g[i - 2] + 1;
            } else {
                dp[i] = dp[i - 1];
                g[i] = min(g[i - 1], g[i - 2] + 1);
            }
        } else {
            if (i) {
                dp[i] = a[i] - r;
                g[i] = 1;
                if (dp[i - 1] > dp[i]) {
                    dp[i] = dp[i - 1];
                    g[i] = g[i - 1];
                }
            } else {
                if (a[i] > r) {
                    dp[i] = a[i] - r;
                    g[i] = 1;
                } else {
                    dp[i] = g[i] = 0;
                }
            }
        }
    }
    return make_pair(dp[n - 1], g[n - 1]);
}

signed main() {
    cin >> n >> k;
    double mx = 0;
    for (int i = 0; i < n; ++i) cin >> a[i], mx = max(mx, 1.0 * a[i]);
    double l = 0, r = mx + 10, mid = 0, ans = 0;
    while (fabs(r - l) > EPS) {
        mid = (l + r) / 2;
        pdi now = get_k(mid);
        if (now.second <= k) {
            r = mid;
        #ifndef debug
            cout << mid << ": " << now.first + now.second * mid << " " << now.second << endl;
        #endif
            ans = now.first;
        } else {
            l = mid;
        }
    }
    cout << (int)(ans + k * mid + 0.5) << "\n";
    return 0;
}