#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int arr[N];
long long pref[N];
int besthub(int n, int l, int X[], long long m){  
    for (int i = 1; i <= n; i++) {
    	arr[i] = X[i - 1];
    	pref[i] = pref[i - 1] + arr[i];
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int l = i, r = n, j;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            int mmid = (i + mid) >> 1;
            long long cost = 1LL * arr[mmid] * (mmid - i + 1) - (pref[mmid] - pref[i - 1]);
            cost += (pref[mid] - pref[mmid]) - 1LL * arr[mmid] * (mid - mmid);
            if (cost <= m) {
                j = mid; l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        res = max(res, j - i + 1);
    }
    return res;
}
