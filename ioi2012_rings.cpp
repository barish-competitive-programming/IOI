#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int MX = 1000006;

int N;

int par[MX], par4[4][MX];
int Find(int x) {
    return par[x] < 0 ? x : (par[x] = Find(par[x]));
}
void Union(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (-par[x] < -par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
}
int Find4(int x, int i) {
    return par4[i][x] < 0 ? x : (par4[i][x] = Find4(par4[i][x], i));
}
void Union4(int x, int y, int i) {
    x = Find4(x, i), y = Find4(y, i);
    if (x == y) return;
    if (-par4[i][x] < -par4[i][y]) swap(x, y);
    par4[i][x] += par4[i][y];
    par4[i][y] = x;
}

void Init(int N_) {
    N = N_;
    for (int i = 0; i < N; i++) {
        par[i] = -1;
        par4[0][i] = par4[1][i] = par4[2][i] = par4[3][i] = -1;
    }
}

vector <int> g[MX];
int has4 = 0, cycle = 0, cycle_size = 0;
int can[4], deg4[4][MX], ok[4], deg[MX];
void add(int a, int b) {
    for (int i = 0; i < 4; i++) {
        if (can[i] == a || can[i] == b || ok[i] == 0) {
            continue;
        }
        deg4[i][a]++, deg4[i][b]++;
        if (deg4[i][a] == 3 || deg4[i][b] == 3) {
            ok[i] = 0;
            continue;
        }
        if (deg4[i][a] == 2 && deg4[i][b] == 2 && Find4(a, i) == Find4(b, i)) {
            ok[i] = 0;
            continue;
        }
        Union4(a, b, i);
    }
}

void wehave4(int v) {
    has4 = 1;
    can[0] = v;
    for (int i = 0; i < 3; i++) {
        can[i + 1] = g[v][i];
    }
    for (int i = 0; i < 4; i++) {
        ok[i] = 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j : g[i]) {
            if (i < j) {
                add(i, j);
            }
        }
    }
}

void Link(int A, int B) {
    if (has4 == 0) {
        deg[A]++, deg[B]++;
        g[A].push_back(B);
        g[B].push_back(A);
        if (deg[A] == 3) {
            wehave4(A);
            return;
        }
        if (deg[B] == 3) {
            wehave4(B);
            return;
        }
        if (deg[A] == 2 && deg[B] == 2 && Find(A) == Find(B)) {
            cycle++;
            cycle_size = -par[Find(A)];
        }
        Union(A, B);
    } else {
        add(A, B);
    }
}

int CountCritical() {
    if (has4 == 0) {
        if (cycle == 1) return cycle_size;
        else if (cycle > 1) return 0;
        else return N;
    }
    return ok[0] + ok[1] + ok[2] + ok[3];
}
