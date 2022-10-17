/*
ARC#151 D
要注意到當 $X_i$ 不同時調換順序無影響，故逐位考慮。而 $i$ 位變化僅影響兩個僅在 $i$ 位不同的數，可認為是一連串矩陣乘積，故分別求之。
*/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MOD = 998244353;
const int MAX_ML = 3;
struct Matrix {
    int m[MAX_ML][MAX_ML];
    int n;
    Matrix(int _n = 0) : n(_n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m[i][j] = 0;
            }
        }
    }
    Matrix I() {
        Matrix res(n);
        for (int i = 0; i < n; ++i) res[i][i] = 1;
        return res;
    }
    void reset(int _n) { n = _n; }
    int* const operator [] (const int k) {
        return m[k];
    }
    Matrix operator * (const Matrix &M) {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    res[i][j] = (res[i][j] + m[i][k] * M.m[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }
    Matrix& operator = (const Matrix &M) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m[i][j] = M.m[i][j];
            }
        }
        return *this;
    }
    void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << m[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

const int MAX_N = 19;
int a[1 << MAX_N];
Matrix M[MAX_N], base[2];
int n, q;

signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) M[i].reset(2), M[i] = M[i].I();
    base[0][0][0] = 1, base[0][0][1] = 1;
    base[0][1][0] = 0, base[0][1][1] = 1;
    base[1][0][0] = 1, base[1][0][1] = 0;
    base[1][1][0] = 1, base[1][1][1] = 1;
    base[0].reset(2), base[1].reset(2);
    for (int i = 0; i < (1 << n); ++i) {
        cin >> a[i];
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        M[x] = base[y] * M[x];

    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            if ((j >> i) & 1) {
                int _j = j ^ (1 << i);
                int a1 = a[j], a2 = a[_j];
            #ifdef debug
                cout << _j << " " << j << ": " << a[_j] << " " << a[j] << endl;
            #endif
                a[j] = (a1 * M[i][0][0] % MOD + a2 * M[i][0][1] % MOD) % MOD;
                a[_j] = (a1 * M[i][1][0] % MOD + a2 * M[i][1][1] % MOD) % MOD;
            #ifdef debug
                cout << "after: " << a[_j] << " " << a[j] << endl;
            #endif
            }
        }
    }
    for (int i = 0; i < (1 << n); ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}