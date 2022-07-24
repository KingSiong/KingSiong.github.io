#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 7;
const int MAX_K = 57;
int n, k, d;
vector<double> x[MAX_N], y[MAX_N];
double mid[MAX_K][MAX_K];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k >> d;
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < k; ++j) {
            int tmp;
            cin >> tmp;
            sum += tmp * tmp;
            x[i].emplace_back(tmp);
        }
        sum = sqrt(sum);
        for (int j = 0; j < k; ++j) x[i][j] /= sum;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            int tmp;
            cin >> tmp;
            y[i].emplace_back(tmp);
        }
    }
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < k; ++j) {
            mid[i][j] = 0;
            for (int t = 0; t < n; ++t) {
                mid[i][j] += y[t][i] * x[t][j];
            }
        }
    }
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < n; ++j) {
            y[j][i] = 0;
            for (int t = 0; t < k; ++t) {
                y[j][i] += mid[i][t] * x[j][t];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            cout << fixed << setprecision(8) << y[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}