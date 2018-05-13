#include <bits/stdc++.h>

using namespace std;

const int maxN = 55;
const int maxM = 55;

int N, M;
int arr[maxN][maxM], p[maxN][maxM];
int dp[maxN][maxM][maxN][maxM];

int solve(int i1, int j1, int i2, int j2) {
    if (i1 == i2 && j1 == j2) {
        return dp[i1][j1][i2][j2] = 0;
    }
    if (dp[i1][j1][i2][j2] != -1) {
        return dp[i1][j1][i2][j2];
    }
    int res = 2000000000;
    for (int i = i1; i < i2; i++) {
        res = min(res, solve(i1, j1, i, j2) + solve(i + 1, j1, i2, j2));
    }
    for (int j = j1; j < j2; j++) {
        res = min(res, solve(i1, j1, i2, j) + solve(i1, j + 1, i2, j2));
    }
    res += p[i2][j2] - p[i2][j1 - 1] - p[i1 - 1][j2] + p[i1 - 1][j1 - 1];
    return dp[i1][j1][i2][j2] = res;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + arr[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(1, 1, N, M) << endl;
    return 0;
}
