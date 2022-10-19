#include <bits/stdc++.h>
#define int long long

using namespace std;

const int INF = 1e18 + 7;
const int MAX_N = 1e5 + 7;
int a[MAX_N];
int con_c[MAX_N], con_m[MAX_N], con_n[MAX_N];
int need_c[MAX_N], need_m[MAX_N];
int n, k;
int lc, pc, lm, pm;
int t, d;
int cnt_c, cnt_m;

int solve(int x, int y) {
#ifdef debug
    cout << x << ", " << y << ": \n";
#endif
    if (x > cnt_c || x + y > cnt_m) return INF;
    int res = x * pc + y * pm;
    int tot = con_c[x] + con_m[x + y] - con_m[x] + con_n[n] - con_n[x + y];
#ifdef debug
    cout << tot << endl;
    cout << need_c[x] << endl; 
    cout << need_m[x + y] - need_m[x] << endl;
#endif
    if (need_c[x] > tot) {
        return INF;
    }
    tot -= need_c[x];
    res += need_c[x] * t;
    if (need_m[x + y] - need_m[x] > tot) {
        return INF;
    }
    tot -= need_m[x + y] - need_m[x];
    res += (need_m[x + y] - need_m[x]) * t;
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    cin >> lc >> pc >> lm >> pm;
    cin >> t >> d;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n, greater<int>());
    for (int i = 1; i <= n; ++i) {
        con_c[i] = max(min(a[i] - lc, d), 0ll);
        con_m[i] = max(min(a[i] - lm, d), 0ll);
        con_n[i] = min(a[i] - 1, d);
        need_c[i] = (lc > a[i] && lc - a[i] <= d) ? lc - a[i] : 0ll;
        need_m[i] = (lm > a[i] && lm - a[i] <= d) ? lm - a[i] : 0ll;
        con_c[i] += con_c[i - 1];
        con_m[i] += con_m[i - 1];
        con_n[i] += con_n[i - 1];
        need_c[i] += need_c[i - 1];
        need_m[i] += need_m[i - 1];
        cnt_c += (a[i] >= lc - d);
        cnt_m += (a[i] >= lm - d);
    }
    int ans = INF;
    for (int i = 0; i <= (n + k - 1) / k; ++i) {
        int j = max(n - i * k, 0ll);
        ans = min(ans, solve(i, j));
    }
    if (ans < INF) {
        cout << ans << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}