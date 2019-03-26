#include <bits/stdc++.h>

using namespace std;

int par[205];
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

int n, q;
set <pair <int, pair <int, int>>> s;
int get(int x, int y, int z) {
    fill(par + 1, par + n + 1, -1);
    s.insert({z, {x, y}});
    int res = 0;
    for (auto it = s.begin(); it != s.end(); it++) {
        int a = (*it).second.first, b = (*it).second.second;
        if (Find(a) != Find(b)) {
            Union(a, b);
            res += (*it).first;
        }
    }
    int ok = 1;
    for (int i = 1; i <= n; i++) {
        if (Find(i) != Find(1)) {
            ok = 0; break;
        }
    }
    if (ok == 0) return -1;
    return res;
}

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    int a, b, c;
    while (q --) {
        cin >> a >> b >> c;
        cout << get(a, b, c) << endl;
    }
    return 0;
}
