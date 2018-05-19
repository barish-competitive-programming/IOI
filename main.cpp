#include <bits/stdc++.h>

using namespace std;

const int N = 20 * 25005;

int t[N][26], mark[N], pref[N], nxt = 1;

void add_trie(string s) {
    int pos = 1;
    for (int i = 0; i < s.size(); i++) {
        if (t[pos][s[i] - 'a'] == 0) {
            t[pos][s[i] - 'a'] = ++nxt;
        }
        pos = t[pos][s[i] - 'a'];
    }
    mark[pos] = 1;
}

void add_largest(string s) {
    int pos = 1;
    for (int i = 0; i < s.size(); i++) {
        pos = t[pos][s[i] - 'a'];
        pref[pos] = 1;
    }
}

string res = "";
void dfs(int v) {
    if (mark[v] == 1) {
        res += 'P';
    }
    int idx = -1;
    for (int i = 0; i < 26; i++) {
        if (pref[t[v][i]] == 1) {
            idx = i;
        } else if (t[v][i] > 0) {
            res += ('a' + i);
            dfs(t[v][i]);
            res += '-';
        }
    }
    if (idx != -1) {
        res += ('a' + idx);
        dfs(t[v][idx]);
    }
}

char s[21];
int main() {
    int n;
    cin >> n;
    int mx_len = 0; string mx_s;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        add_trie(s);
        if (strlen(s) > mx_len) {
            mx_len = strlen(s);
            mx_s = s;
        }
    }
    add_largest(mx_s);
    dfs(1);
    printf("%d\n", (int)res.size());
    for (int i = 0; i < res.size(); i++) {
        printf("%c\n", res[i]);
    }
    return 0;
}
