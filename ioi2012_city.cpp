#include "grader.h"
#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

const int MOD = 1000000000;
const int N = 100005;

vector <int> g[N];

long long sum[N], total, w[N];
void dfs(int v, int par = -1) {
  sum[v] = w[v];
  total += w[v];
  for (int i : g[v]) {
    if (i != par) {
      dfs(i, v);
      sum[v] = (sum[v] + sum[i]) % MOD;
    }
  }
}

int solve(vector <pair <int, int>> v) {
  sort(v.begin(), v.end());
  int nxt = 0, i = 0;
  map <pair <int, int>, int> id;
  set <pair <int, int>> edg;
  while(i < v.size()) {
    int j = i, cnt = 0;
    while(j < v.size() && v[i].x == v[j].x) {
      if (j > i && v[j].y != v[j - 1].y + 1) {
        w[nxt] = cnt;
        cnt = 0;
        nxt++;
      }
      id[v[j]] = nxt;
      pair <int, int> prev = {v[j].x - 1, v[j].y};
      if (*lower_bound(v.begin(), v.end(), prev) == prev) {
        if (!edg.count({nxt, id[prev]})) {
          g[nxt].push_back(id[prev]);
          g[id[prev]].push_back(nxt);
          edg.insert({nxt, id[prev]});
          edg.insert({id[prev], nxt});
        }
      }
      cnt++;
      j++;
    }
    i = j;
    w[nxt++] = cnt;
  }
  total = 0;
  dfs(0);
  int res = 0;
  for (int i = 0; i < nxt; i++) {
    res = (res + 1LL * sum[i] * (total - sum[i]) % MOD) % MOD;
    g[i].clear();
  }
  return res;
}

int DistanceSum(int N, int *X, int *Y) {
  vector <pair <int, int>> vx, vy;
  for (int i = 0; i < N; i++) {
    vx.push_back({X[i], Y[i]});
    vy.push_back({Y[i], X[i]});
  }
  return (solve(vx) + solve(vy)) % MOD;
}
