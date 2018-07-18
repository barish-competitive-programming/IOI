#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;
const int maxx = 100005;

int used[maxx], p[maxx];
vector <pair <int, int>> g[maxx];

int cur_max = 0, cur_node = -1;
void dfs(int v, int par = -1, int d = 0) {
    used[v] = 1;
    p[v] = par;
    if (d > cur_max) {
        cur_max = d, cur_node = v;
    }
    for (auto j : g[v]) {
        if (j.first != par) {
            dfs(j.first, v, d + j.second);
        }
    }
}

map <pair <int, int>, int> cost;
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    for (int i = 0; i < M; i++) {
        g[A[i]].push_back({B[i], T[i]});
        g[B[i]].push_back({A[i], T[i]});
        cost[{A[i], B[i]}] = cost[{B[i], A[i]}] = T[i];
    }
    vector <pair <int, int>> centers;
    for (int i = 0; i < N; i++) {
        if (used[i] == 0) {
            cur_max = 0, cur_node = -1;
            dfs(i);
            if (cur_node == -1) {
                centers.push_back({0, i});
                continue;
            }
            int u = cur_node;
            cur_max = 0, cur_node = -1;
            dfs(u);
            int v = cur_node;
            vector <int> path;
            while (v != u) {
                path.push_back(v);
                v = p[v];
            } path.push_back(u);
            int cur = 0, best_res = INF, best_v = path[0];
            for (int j = 1; j < path.size(); j++) {
                cur += cost[{path[j], path[j - 1]}];
                if (max(cur, cur_max - cur) < best_res) {
                    best_res = max(cur, cur_max - cur);
                    best_v = path[j];
                }
            }
            centers.push_back({best_res, best_v});
        }
    }
    sort(centers.rbegin(), centers.rend());
    for (int i = 1; i < centers.size(); i++) {
        g[centers[0].second].push_back({centers[i].second, L});
        g[centers[i].second].push_back({centers[0].second, L});
    }
    cur_max = 0, cur_node = -1;
    dfs(0);
    int u = cur_node;
    cur_max = 0, cur_node = -1;
    dfs(u);
    return cur_max;
}
