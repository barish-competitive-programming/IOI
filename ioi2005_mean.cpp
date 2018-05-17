#include <bits/stdc++.h>

using namespace std;

const int N = 5 * 1000005;

int m[N];
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
    }
    long long high = m[1], low = 2 * m[1] - m[2];
    long long odd_sum, even_sum;

    odd_sum = 2 * m[1], even_sum = 0;
    for (int i = 3; i <= n; i += 2) {
        odd_sum += m[i], even_sum -= 2 * m[i - 1];
        high = min(high, odd_sum + even_sum);
        odd_sum += m[i];
    }

    odd_sum = 2 * m[1], even_sum = -2 * m[2];
    for (int i = 4; i <= n; i += 2) {
        odd_sum += 2 * m[i - 1], even_sum -= m[i];
        low = max(low, odd_sum + even_sum);
        even_sum -= m[i];
    }
    cout << max(0LL, high - low + 1) << endl;;
    return 0;
}
