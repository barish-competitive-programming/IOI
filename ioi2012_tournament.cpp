#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int N = 100005;

int t[N << 2], id[N << 2];
void build(int v, int l, int r) {
    if (l == r) {
        t[v] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    t[v] = t[v << 1] + t[v << 1 | 1];
}
void del(int v, int l, int r, int i) {
    if (l == r) {
        t[v] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid) {
        del(v << 1, l, mid, i);
    } else {
        del(v << 1 | 1, mid + 1, r, i);
    }
    t[v] = t[v << 1] + t[v << 1 | 1];
}
int get(int v, int l, int r, int k) {
    if (l == r) {
        return r;
    }
    int mid = (l + r) >> 1;
    if (t[v << 1] >= k) {
        return get(v << 1, l, mid, k);
    } else {
        return get(v << 1 | 1, mid + 1, r, k - t[v << 1]);
    }
}

vector <int> g[N << 1];
int par[N << 1][19], lvl[N << 1];

void dfs(int v, int p = 0) {
    lvl[v] = lvl[p] + 1;
    par[v][0] = p;
    for (int i = 1; i < 19; i++) {
        par[v][i] = par[par[v][i - 1]][i - 1];
    }
    for (int i : g[v]) {
        if (i != p) {
            dfs(i, v);
        }
    }
}
int lca(int x, int y) {
    if (lvl[x] < lvl[y]) swap(x, y);
    int d = lvl[x] - lvl[y];
    for (int i = 18; i >= 0; i--) {
        if (d & (1 << i)) {
            x = par[x][i];
        }
    }
    if (x == y) return x;
    for (int i = 18; i >= 0; i--) {
        if (par[x][i] != par[y][i]) {
            x = par[x][i], y = par[y][i];
        }
    }
    return par[x][0];
}

int lf[N], rg[N], root[N];
int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
    for (int i = 1; i <= N; i++) {
        id[i] = i;
    }
    build(1, 1, N);
    int nxt = N;
    for (int i = 0; i < C; i++) {
        S[i]++, E[i]++;
        ++nxt;
        vector <int> D;
        for (int j = S[i]; j <= E[i]; j++) {
            int cur = get(1, 1, N, j);
            g[nxt].push_back(id[cur]);
            g[id[cur]].push_back(nxt);
            if (j > S[i]) {
                D.push_back(cur);
            }
        }
        id[get(1, 1, N, S[i])] = nxt;
        for (int j : D) {
            del(1, 1, N, j);
        }
    }
    dfs(nxt);
    vector <int> lft;
    for (int i = 0; i < N - 1; i++) {
        if (K[i] > R) {
            lft.push_back(i + 1);
        }
    }
    if (lft.empty()) return 0;
    int rgt = N + 1, res = -1, pos;
    for (int i = N; i >= 1; i--) {
        if (!lft.empty() && i == lft.back()) {
            rgt = i + 1;
            lft.pop_back();
        }
        int mx = N + 1;
        if (rgt <= N) {
            mx = min(mx, lvl[i] - lvl[lca(i, rgt)]);
        }
        if (!lft.empty()) {
            mx = min(mx, lvl[i] - lvl[lca(i, lft.back())]);
        }
        if (mx >= res) {
            res = mx, pos = i - 1;
        }
    }
    return pos;
}
