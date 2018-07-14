#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int INF = 2000000000;
const int maxx = 2000005;

#define mn first
#define mx second

pair <int, int> t[maxx << 2];

void relax(int v, int l, int r) {
    if (l != r) {
        int lc = v << 1, rc = v << 1 | 1;
        t[lc] = {max(min(t[lc].mn, t[v].mn), t[v].mx), max(min(t[lc].mx, t[v].mn), t[v].mx)};
        t[rc] = {max(min(t[rc].mn, t[v].mn), t[v].mx), max(min(t[rc].mx, t[v].mn), t[v].mx)};
    }
}

void update(int v, int l, int r, int i, int j, int val, int oq) {
    relax(v, l, r);
    if (i > r || j < l) {
        return;
    }
    if (i <= l && r <= j) {
        if (oq == 1) {
            t[v].mn = max(t[v].mn, val);
            t[v].mx = max(t[v].mx, val);
        } else {
            t[v].mn = min(t[v].mn, val);
            t[v].mx = min(t[v].mx, val);
        }
        return;
    }
    t[v].mn = INF, t[v].mx = -INF;
    int mid = (l + r) >> 1;
    update(v << 1, l, mid, i, j, val, oq);
    update(v << 1 | 1, mid + 1, r, i, j, val, oq);
}
int query(int v, int l, int r, int i) {
    relax(v, l, r);
    if (l == r) {
        return t[v].mn;
    }
    int mid = (l + r) >> 1;
    if (i <= mid) {
        return query(v << 1, l, mid, i);
    } else {
        return query(v << 1 | 1, mid + 1, r, i);
    }
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
    for (int i = 0; i < k; i++) {
        update(1, 1, n, left[i] + 1, right[i] + 1, height[i], op[i]);
    }
    for (int i = 1; i <= n; i++) {
        finalHeight[i - 1] = query(1, 1, n, i);
    }
    return;
}

