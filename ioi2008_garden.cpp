#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;

int p[N];
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    string s; cin >> s;
    p[0] = 1;
    for (int i = 1; i <= n; i++) p[i] = 2 * p[i - 1] % m;
    int res = 1;
    int cur = 0, mn = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            cur++, mx = max(mx, cur);
        } else {
            int rem = n - i - 1;
            int low = cur + 1, mxx = max(low, mx);
            if (mxx - mn == 1) {
                res += p[rem >> 1] + p[rem + 1 >> 1] - 1;
                res = (res + m) % m;
            } else if (mxx - mn == 2) {
                res += p[rem + (cur == mn) >> 1];
                res %= m;
            }
            cur--, mn = min(mn, cur);
        }
    }
    cout << res << endl;
    return 0;
}
