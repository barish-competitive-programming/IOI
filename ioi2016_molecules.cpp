#include "molecules.h"
#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
    vector <pair <int, int>> v;
    int n = w.size();
    for (int i = 0; i < n; i++) {
        v.push_back({w[i], i});
    }
    sort(v.begin(), v.end());
    vector <long long> pref(n + 1); pref[n] = 0;
    pref[0] = v[0].F;
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1] + v[i].F;
    }
    pair <int, int> res = {-1, -1};
    for (int i = 0; i < n; i++) {
        int lf = i, rg = n - 1, best = -1;
        while (rg - lf >= 0) {
            int mid = (lf + rg) >> 1;
            long long sum = pref[mid] - pref[(i == 0 ? n : i - 1)];
            if (1LL * l <= sum && sum <= 1LL * u) {
                best = mid;
                break;
            }
            if (sum < l) {
                lf = mid + 1;
            } else if (sum > u) {
                rg = mid - 1;
            }
        }
        if (best != -1) {
            res = {i, best};
            break;
        }
    }
    if (res.F == -1) {
        return vector<int>();
    }
    vector <int> ans;
    for (int i = res.F; i <= res.S; i++) {
        ans.push_back(v[i].S);
    }
    return ans;
}
