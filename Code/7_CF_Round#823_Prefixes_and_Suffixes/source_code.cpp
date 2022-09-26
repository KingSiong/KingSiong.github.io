/*

反串對應位置對不變，故 a-b 對為偶數；a-a 為奇數最多祇有一個。

*/
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 27;
string s, t;
int cnt[MAX_N][MAX_N];
int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> s >> t;
        reverse(t.begin(), t.end());
    #ifdef debug
        cout << s << "\n" << t << "\n";
    #endif
        for (int i = 0; i < n; ++i) {
            int a = min((int)(s[i] - 'a'), (int)(t[i] - 'a'));
            int b = max((int)(s[i] - 'a'), (int)(t[i] - 'a'));
            ++cnt[a][b];
        }
        bool flag = true;
        int cnt_odd = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = i + 1; j < 26; ++j) {
                if (cnt[i][j] & 1) flag = false;
            }
            if (cnt[i][i] & 1) ++cnt_odd;
        }
        if (cnt_odd > 1) flag = false;
        if (cnt_odd == 1 && (n % 2 == 0)) flag = false;
        if (flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        for (int i = 0; i < 26; ++i) for (int j = 0; j < 26; ++j) cnt[i][j] = 0;
    }
    return 0;
}