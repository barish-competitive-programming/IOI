#include <bits/stdc++.h>

using namespace std;

int dx[] = {0, 0, +1, -1};
int dy[] = {-1, +1, 0, 0};

int n, m, k;
char arr[1200][1200];
int good[1200][1200];

int has_one_marked_neighbor(int i, int j) {
    return (good[i - 1][j] + good[i + 1][j] + good[i][j - 1] + good[i][j + 1]) == 1;
}

int grid(int i, int j) {
    return 1 <= i && i <= n && 1 <= j && j <= m && arr[i][j] == '.';
}

int solve_empty() {
    /*
    good[2][2] = 1;
    queue <pair <int, int>> q;
    q.push({2, 2});
    while(!q.empty()) {
        pair <int, int> cur = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int x = cur.first + dx[i], y = cur.second + dy[i];
            if (grid(x, y) == 1 && has_one_marked_neighbor(x, y) == 1) {
                good[x][y] = 1;
                q.push({x, y});
            }
        }
    }
    */
    /*
    good[2][2] = 1;
    int need;
    do {
        need = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (good[i][j] == 0 && has_one_marked_neighbor(i, j) == 1) {
                    good[i][j] = need = 1;
                }
            }
        }
    } while(need == 1);
    */
    int T = (m & 1 == 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (((!(i % 3) && (j & 1) == T) || j == m - 1 || (i % 3 == 2 && j != m-2 && j % 2 == !T) || (i % 3 == 2 && j == m-3) || (i == n-1 && i % 3 == 0)) && !(i % 3 == 2 && j == m-2)) {
                good[i + 1][j + 1] = 0;
            } else {
                good[i + 1][j + 1] = 1;
            }
        }
    }
    for (int i = 4; i <= n; i += 3) {
        good[i][1] = 1, good[i][2] = 0;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (good[i][j] == 0) {
                arr[i][j] = 'X';
            } else {
                cnt += has_one_marked_neighbor(i, j);
            }
        }
    }
    return cnt;
}

int good_tmp[1200][1200];
vector <pair <int, int>> cells;
int solve_general() {
    int res = 0;
    for (int it = 1; it <= 1000; it++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                good[i][j] = 0;
            }
        }
        int x = rand() % n + 1, y = rand() % m + 1;
        while (arr[x][y] == '#') {
            x = rand() % n + 1, y = rand() % m + 1;
        }
        good[x][y] = 1;
        random_shuffle(cells.begin(), cells.end());
        int need;
        do {
            need = 0;
            for (pair <int, int> cur : cells) {
                if (good[cur.first][cur.second] == 0 && has_one_marked_neighbor(cur.first, cur.second) == 1) {
                    good[cur.first][cur.second] = 1;
                    need = 1;
                }
            }
        } while(need == 1);
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (good[i][j] == 1 && has_one_marked_neighbor(i, j) == 1) {
                    cnt++;
                }
            }
        }
        if (cnt > res) {
            res = cnt;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    good_tmp[i][j] = good[i][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            good[i][j] = good_tmp[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (good[i][j] == 1) {
                arr[i][j] = '.';
            } else if (arr[i][j] != '#') {
                arr[i][j] = 'X';
            }
        }
    }
    return res;
}

int main() {
    srand(3169);
    freopen("01.in","r",stdin);
    freopen("01.out","w",stdout);
    ios_base :: sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == '.') cells.push_back({i, j});
        }
    }
    int cnt = solve_general();
    cerr << "SCORE = " << min(10.0, 10.0 * cnt / k) << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    return 0;
}
