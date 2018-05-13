#include <bits/stdc++.h>

using namespace std;

const int maxN = 2005;
const int maxT = 2005;


int arr[maxN][maxT], solved[maxT], ac[maxN];
pair <int, int> score[maxN];

bool cmp(pair <int, int> x, pair <int, int> y) {
    if (x.first == y.first) {
        if (ac[x.second] == ac[y.second]) {
            return x.second < y.second;
        }
        return ac[x.second] > ac[y.second];
    }
    return x.first > y.first;
}

int main() {
    int N, T, P;
    cin >> N >> T >> P;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= T; j++) {
            cin >> arr[i][j];
            solved[j] += arr[i][j];
            ac[i] += arr[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        score[i].second = i;
        for (int j = 1; j <= T; j++) {
            score[i].first += (arr[i][j] == 1) * (N - solved[j]);
        }
    }
    int Pscore = score[P].first, Prank = 0;
    sort(score + 1, score + N + 1, cmp);
    for (int i = 1; i <= N; i++) {
        if (score[i].second == P) {
            Prank = i;
            break;
        }
    }
    cout << Pscore << " " << Prank << endl;
    return 0;
}
