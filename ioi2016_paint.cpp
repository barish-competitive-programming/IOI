#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 200005;
const int K = 205;

int n, k; string s; vector <int> c;
int sum_w[N], w[N], b[N];
int dp[N][K];

int w_sum(int l, int r) {
	return sum_w[r] - sum_w[l - 1];
}
void add_w(int l, int r) {
	w[l]++, w[r + 1]--;;
}
void add_b(int l, int r) {
	b[l]++, b[r + 1]--;
}

int update_w(int i, int j);
int update_b(int i, int j);
int solve(int i, int j);

int update_w(int i, int j) {
	int ret = solve(i + 1, j);
	if (ret == 1) {
		add_w(i, i);
	}
	return ret;
}
int update_b(int i, int j) {
	int id = i + c[j];
	if (id > n || w_sum(i, id - 1) > 0 || (id < n && s[id] == 'X')) {
		return 0;
	}
	int ret = solve(id + 1, j + 1);
	if (ret == 1) {
		if (id < n) {
			add_w(id, id);
		}
		add_b(i, id - 1);
	}
	return ret;
}
int solve(int i, int j) {
	if (i >= n) {
		return j == k;
	}
	int &ret = dp[i][j];
	if (ret != -1) {
		return ret;
	}
	ret = 0;
	if (j == k) {
		if (s[i] == 'X') {
			return ret = 0;
		} else {
			return ret = update_w(i, j);
		}
	}
	if (s[i] == '_') {
		return ret = update_w(i, j);
	} else if (s[i] == 'X') {
		return ret = update_b(i, j);
	}
	return ret = update_w(i, j) | update_b(i, j);
}

string solve_puzzle(string xs, vector<int> xc) {
	memset(dp, -1, sizeof(dp));
	s = xs, c = xc;
	n = s.size(), k = c.size();
	for (int i = 0; i < n; i++) {
		sum_w[i] = sum_w[i - 1] + (s[i] == '_');
	}
	solve(0, 0);
	for (int i = 1; i < n; i++) {
		w[i] += w[i - 1], b[i] += b[i - 1];
	}
	string res = "";
	for (int i = 0; i < n; i++) {
		if (w[i] > 0 && b[i] > 0) {
			res += '?';
		} else if (w[i] > 0) {
			res += '_';
		} else {
			res += 'X';
		}
	}
	return res;
}
