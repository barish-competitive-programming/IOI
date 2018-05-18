#include "quality.h"
#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int arr[N][N], p[N][N];
int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	int l = 1, r = R * C, best;
	while (r - l >= 0) {
        int mid = (l + r) >> 1;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                arr[i][j] = (Q[i][j] <= mid) - (Q[i][j] >= mid);
            }
        }
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + arr[i - 1][j - 1];
            }
        }
        int ok = 0;
        for (int i = 1; i + H - 1 <= R; i++) {
            for (int j = 1; j + W - 1 <= C; j++) {
                int ii = i + H - 1, jj = j + W - 1;
                if (p[ii][jj] - p[i - 1][jj] - p[ii][j - 1] + p[i - 1][j - 1] >= 0) {
                    ok = 1;
                    break;
                }
            }
        }
        if (ok == 1) {
            best = mid, r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return best;
}
