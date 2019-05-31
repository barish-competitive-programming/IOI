#include <bits/stdc++.h>
#include "grader.h"

#define F first
#define S second

using namespace std;

const int N = 200005;

int n, k;
vector <int> g[N];
vector <pair <int, int>> gw[N]; /// just for simplicity in the code
int del[N], sub[N];
int res = N;

void calc(int v, int p = -1) {
    sub[v] = 1;
    for (int i : g[v]) {
        if (i != p && del[i] == 0) {
            calc(i, v);
            sub[v] += sub[i];
        }
    }
}
int centroid(int v, int r, int p = -1) {
    for (int i : g[v]) {
        if (i != p && del[i] == 0 && sub[i] > r) {
            return centroid(i, r, v);
        }
    }
    return v;
}
map<int, int> dp;
vector <pair <int, int>> vec;
void dfs(int v, int p = -1, int cur = 0, int dis = 0) {
    if (cur > k) return;
    if (dp.count(k - cur)) {
        res = min(res, dp[k - cur] + dis);
    }
    for (auto i : gw[v]) {
        if (i.F != p && del[i.F] == 0) {
            dfs(i.F, v, cur + i.S, dis + 1);
        }
    }
    vec.push_back({cur, dis});
}
void decompose(int v, int p = -1) {
    calc(v);
    int c = centroid(v, sub[v] >> 1);
    del[c] = 1;
    dp.clear();
    dp[0] = 0;
    for (auto i : gw[c]) {
        if (del[i.F] == 1) continue;
        vec.clear();
        dfs(i.F, c, i.S, 1);
        for (auto j : vec) {
            if (!dp.count(j.F)) dp[j.F] = j.S;
            else dp[j.F] = min(dp[j.F], j.S);
        }
    }
    for (int i : g[c]) {
        if (i != p && del[i] == 0) {
            decompose(i, c);
        }
    }
}

int best_path(int N, int K, int H[][2], int L[]) {
    n = N, k = K;
    for (int i = 0; i < n - 1; i++) {
        g[H[i][0]].push_back(H[i][1]);
        g[H[i][1]].push_back(H[i][0]);
        gw[H[i][0]].push_back({H[i][1], L[i]});
        gw[H[i][1]].push_back({H[i][0], L[i]});
    }
    decompose(0);
    if (res > n) res = -1;
    return res;
}
