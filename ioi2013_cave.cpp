#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

const int maxx = 5005;

int comb[maxx], id[maxx];
int used[maxx];

void change(int l, int r) {
    for (int i = l; i <= r; i++) {
        if (used[i] == 0) {
            comb[i] ^= 1;
        }
    }
}

void exploreCave(int N) {
    for (int i = 0; i < N; i++) {
        int l = 0, r = N - 1, best;
        int flag = tryCombination(comb) == i;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            change(l, mid);
            if ((tryCombination(comb) == i) == flag) {
                change(l, mid);
                l = mid + 1;
            } else {
                change(l, mid);
                r = mid - 1, best = mid;
            }
        }
        used[best] = 1;
        id[best] = i;
        comb[best] = flag;
    }
    answer(comb, id);
}
