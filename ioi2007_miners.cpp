#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int dp[2][4][4][4][4];

int get(char c) {
    if (c == 'M') {
        return 1;
    }
    if (c == 'F') {
        return 2;
    }
    return 3;
}

int cost(int x, int y, int z) {
    int res = 0;
    for (int i = 1; i <= 3; i++) {
        if (x == i || y == i || z == i) {
            res++;
        }
    }
    return res;
}

int main() {
    int n; string s;
    cin >> n >> s;
    int alter = 0;
    for (int i = n - 1; i >= 0; i--, alter ^= 1) {
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                for (int a = 0; a < 4; a++) {
                    for (int b = 0; b < 4; b++) {
                        dp[alter][x][y][a][b] = max(dp[alter ^ 1][y][get(s[i])][a][b] + cost(x, y, get(s[i])), dp[alter ^ 1][x][y][b][get(s[i])] + cost(a, b, get(s[i])));
                    }
                }
            }
        }
    }
    cout << dp[alter ^ 1][0][0][0][0] << endl;
    return 0;
}
