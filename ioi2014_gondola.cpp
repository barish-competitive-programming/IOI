#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second

const int N = 100005;
const int MOD = 1000000009;

int valid(int n, int A[]) {
    set <int> S(A, A + n);
    if (S.size() != n) return 0;
    for (int i = 0, k = -MOD; i < n; i++) {
        if (A[i] <= n) {
            if (k == -MOD) k = (A[i] - i - 1 + n) % n;
            else if (k != (A[i] - i - 1 + n) % n) return 0;
        }
    }
    return 1;
}

int replacement(int n, int A[], int ret[]) {
    int k = -MOD, ptr = 0;
    vector <int> B(N);
    for (int i = 0; i < n; i++) {
        if (A[i] <= n) {
            k = (A[i] - i - 1 + n) % n;
        }
    }
    vector <pair <int, int>> v;
    for(int i = 0; i < n; i++) {
        if (k == -MOD) B[i] = A[i];
        else B[i] = A[(i - k + n) % n];
        if (B[i] > n) v.push_back({B[i], i + 1});
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        while (ptr + n < v[i].F) {
            ret[ptr++] = v[i].S;
            v[i].S = ptr + n;
        }
    }
    return ptr;
}

int modpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = 1LL * ret * a % MOD;
        a = 1LL * a * a % MOD;
    }
    return ret;
}

int countReplacement(int n, int A[]) {
    if (!valid(n, A)) return 0;
    vector <int> v;
    for (int i = 0; i < n; i++) if(A[i] > n) v.push_back(A[i]);
    sort (v.begin(), v.end());
    int ans = 1;
    for (int i = 0; i < v.size(); i++) {
        int b = v.size() - i;
        int p = v[i] - (i ? v[i - 1] + 1 : n + 1);
        ans = 1LL * ans * modpow(b, p) % MOD;
    }
    if (v.size() == n) ans = 1LL * ans * n % MOD;
    return ans;
}
