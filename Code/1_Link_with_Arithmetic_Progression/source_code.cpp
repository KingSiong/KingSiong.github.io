#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 7;
int T, n;
int a[MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        double xbar = 1.0 * (n - 1) / 2, ybar = 0;
        for (int i = 0; i < n; ++i) cin >> a[i], ybar += a[i];
        ybar /= 1.0 * n;
        double u = 0, d = 0;
        for (int i = 0; i < n; ++i) {
            u += 1.0 * (i - xbar) * (a[i] - ybar);
            d += 1.0 * (i - xbar) * (i - xbar);
        }
        double b1 = u / d, b0 = ybar - b1 * xbar;
        double ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += 1.0 * (a[i] - i * b1 - b0) * (a[i] - i * b1 - b0);
        }
        cout << fixed << setprecision(10) << ans << "\n";
    }
    return 0;
}