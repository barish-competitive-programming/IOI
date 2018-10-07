#include "wiring.h"
#include <bits/stdc++.h>

const int N = 200005;
const long long INFLL = 4000000000000000000LL;

using namespace std;

long long dp[N], f[N], pref[N];
int last[N];

long long min_total_length(vector<int> r, vector<int> b) {
    int nr = r.size(), nb = b.size(), n = nr + nb;
	vector <pair <int, int>> v;
	for (int i = 0; i < nr; i++) {
        v.push_back({r[i], 0});
	}
	for (int i = 0; i < nb; i++) {
        v.push_back({b[i], 1});
	}
	sort(v.begin(), v.end());
	dp[0] = INFLL, pref[0] = v[0].first;
    last[0] = -1;
    for (int i = 1; i < n; i++) {
        dp[i] = INFLL;
        pref[i] = pref[i - 1] + v[i].first;
        last[i] = v[i].second == v[i - 1].second ? last[i - 1] : i - 1;
        for (int j = last[i - 1] + 1; j <= last[i]; j++) {
            f[j] = min(dp[j], f[j - 1] + v[i].first - v[j].first);
        }
        if (last[i] == -1) continue;
        dp[i] = min(dp[i], dp[i - 1] + v[i].first - v[last[i]].first);
        /// last[i]+1 ... i same color
        /// last[last[i]]+1 ... last[i] same color
        if (last[last[i]] < last[i] - (i - last[i]) + 1) {
            dp[i] = min(dp[i], (pref[i] - pref[last[i]]) - (pref[last[i]] - pref[last[i] - (i - last[i])]) + dp[last[i] - (i - last[i])]);
        }
    }
    return dp[n - 1];
}
