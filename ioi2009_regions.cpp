#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define F first
#define S second

using namespace std;

const int N = 200005, K = 25001;
const int INF = 1e9;
const int B = 250;
const int P = N / B + 5;

int n, r, q, p[N], a[N];
int prec[P][K];
vector <int> g[N], has[K];

int id[K], cnt[K];
void dfs(int v, int cnt, int start) {
    cnt += start == a[v];
    if (a[v] != start) prec[id[start]][a[v]] += cnt;
    for (int i : g[v]) {
        dfs(i, cnt, start);
    }
}

int in[N], out[N], T = 0;
vector <int> ins[K];
void dfs(int v) {
    in[v] = ++T;
    ins[a[v]].pb(in[v]);
    for (int i : g[v]) {
        dfs(i);
    }
    out[v] = T;
}

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> r >> q;
    for (int i = 1; i <= n; i++) {
        if (i == 1) cin >> a[i];
        else cin >> p[i] >> a[i];
    }
    for (int i = 2; i <= n; i++) {
        g[p[i]].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++, has[a[i]].pb(i);
    }
    int cur = 0;
    for (int i = 1; i <= r; i++) {
        if (cnt[i] > B) {
            id[i] = ++cur;
            dfs(1, 0, i);
        }
    }
    dfs(1);
    while(q--) {
        int p, q; cin >> p >> q;
        if (cnt[p] > B) {
            cout << prec[id[p]][q] << endl;
            continue;
        }
        int res = 0;
        for (int i : has[p]) {
            res += upper_bound(ins[q].begin(), ins[q].end(), out[i]) -
                   lower_bound(ins[q].begin(), ins[q].end(), in[i]);
        }
        cout << res << endl;
    }
    return 0;
}
