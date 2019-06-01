#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int N = 100005;

vector <pair <int, int>> g[N];
int used[N];

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
    for (int i = 0; i < M; i++) {
        g[R[i][0]].push_back({R[i][1], L[i]});
        g[R[i][1]].push_back({R[i][0], L[i]});
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 0; i < K; i++) {
        pq.push({0, P[i]});
        used[P[i]] = 1;
    }
    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        long long d = cur.first; int v = cur.second;
        if (++used[v] != 2) continue;
        if (v == 0) {
            return d;
        }
        for (auto i : g[v]) {
            pq.push({d + i.second, i.first});
        }
    }
}
