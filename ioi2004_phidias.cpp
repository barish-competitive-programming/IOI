#include <bits/stdc++.h>

using namespace std;

int w[605], h[605], dp[605][605];
int main() {
    int n, m, k;
    cin >> m >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> w[i] >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = i * j;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int id = 1; id <= k; id++) {
                if (i - h[id] >= 0 && w[id] <= j) {
                    dp[i][j] = min(dp[i][j], dp[i - h[id]][j] + h[id] * (j % w[id]));
                    if (h[id] < i) dp[i][j] = min(dp[i][j], dp[i - h[id]][j] + dp[h[id]][j]);
                }
                if (j - w[id] >= 0 && h[id] <= i) {
                    dp[i][j] = min(dp[i][j], dp[i][j - w[id]] + w[id] * (i % h[id]));
                    if (w[id] < j) dp[i][j] = min(dp[i][j], dp[i][j - w[id]] + dp[i][w[id]]);
                }
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
