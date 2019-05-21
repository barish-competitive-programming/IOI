#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

void ComputeAdvice(int *C, int N, int K, int M) {
  vector <int> has(N, 0);
  for (int i = 0; i < K; i++) {
    has[i] = 1;
  }
  vector <int> nxt(N + K), last(N, N + K), c(N + K);
  for (int i = 0; i < K; i++) {
    c[i] = i;
  }
  for (int i = 0; i < N; i++) {
    c[i + K] = C[i];
  }
  for (int i = N + K - 1; i >= 0; i--) {
    nxt[i] = last[c[i]];
    last[c[i]] = i;
  }
  set <pair <int, int>> s;
  vector <int> change(N + K, 0);
  for (int i = 0; i < K; i++) {
    s.insert({nxt[i], i});
  }
  for (int i = K; i < N + K; i++) {
    if (has[c[i]] == 1) {
      s.insert({nxt[i], i});
      continue;
    }
    auto cur = *s.rbegin();
    change[cur.second] = 1;
    has[c[i]] = 1;
    has[c[cur.second]] = 0;
    s.erase(cur);
    s.insert({nxt[i], i});
  }
  for (int i = 0; i < N + K; i++) {
    WriteAdvice(change[i]);
  }
}

void Assist(unsigned char *A, int N, int K, int R) {
  vector <int> cur, has(N, 0);
  for (int i = 0; i < K; i++) {
    has[i] = 1;
    if (A[i] == 1) {
      cur.push_back(i);
    }
  }
  for (int i = 0; i < N; i++) {
    int c = GetRequest();
    if (has[c] == 0) {
      PutBack(cur.back());
      has[cur.back()] = 0;
      cur.pop_back();
      has[c] = 1;
    }
    if (A[i + K] == 1) {
      cur.push_back(c);
    }
  }
}
