#include "grader.h"
#include "memory.h"
#include <bits/stdc++.h>

using namespace std;

pair <int, int> res[25];

void play() {
    for (int i = 0; i < 25; i++) {
        res[i].first = res[i].second = -1;
    }
    for (int i = 1; i <= 50; i++) {
        int x = faceup(i) - 'A';
        if (res[x].first == -1) {
            res[x].first = i;
        } else {
            res[x].second = i;
        }
    }
    for (int i = 0; i < 25; i++) {
        faceup(res[i].first);
        faceup(res[i].second);
    }
    return;
}
