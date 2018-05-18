#include "traffic.h"
#include <bits/stdc++.h>

using namespace std;

const int INF = 2000000000;
const int MX = 1000005;

int dp[MX];
int cost[MX];
vector <int> g[MX];

void dfs(int v, int par) {
    dp[v] = cost[v];
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] != par) {
            dfs(g[v][i], v);
            dp[v] += dp[g[v][i]];
        }
    }
}

int res = INF, idx = -1;
void dfs(int v, int par, int cst) {
    int cur = cst;
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] != par) {
            dfs(g[v][i], v, cst + dp[v] - dp[g[v][i]]);
            cur = max(cur, dp[g[v][i]]);
        }
    }
    if (cur < res) {
        res = cur, idx = v;
    }
}

int LocateCentre(int N, int pp[], int S[], int D[]) {
    cost[N - 1] = pp[N - 1];
    for (int i = 0; i < N - 1; i++) {
        g[S[i]].push_back(D[i]);
        g[D[i]].push_back(S[i]);
        cost[i] = pp[i];
    }
    dfs(0, -1);
    dfs(0, -1, 0);
    return idx;
}
