#include "prize.h"
#include <bits/stdc++.h>

#define pii pair<int,int>

using namespace std;

vector <int> v;

int go (int l, int r, pii left, pii right) {
	if (l > r) {
		return -1;
	}
	int mid = (l + r) >> 1;
	v = ask(mid);
	pii c = {v[0], v[1]};
	if (v[0] == 0 && v[1] == 0) {
		return mid;
	}
	if (l == r) {
		return -1;
	}
	int ret = -1;
	if (c.second > 0 && c != right) {
		ret = go(mid + 1, r, c, right);
	}
	if (ret == -1 && c.first > 0 && c != left) {
		ret = go(l, mid - 1, left, c);
	}
	return ret;
}

int find_best(int n) {
	return go(0, n - 1, {-1, -1}, {-1, -1});
}
