#include "boxes.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 10000005;

long long pref[N], suff[N];

long long delivery(int N, int K, int L, int p[]) {
    for (int i = 0; i < N; i++) {
        pref[i] = (i - K >= -1 ? pref[i - K] + p[i] : p[i]) + min(p[i], L - p[i]);
    }
    for (int i = N - 1; i >= 0; i--) {
        suff[i] = (i + K <= N ? suff[i + K] + L - p[i] : L - p[i]) + min(p[i], L - p[i]);
    }
    long long res = 2000000000000000000;
    for (int i = -1; i < N; i++) {
        res = min(res, pref[i] + suff[i + 1]);
    }
    return res;
}
