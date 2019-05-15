#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

struct node{
    char cur;
    int sz;
    node *par[20];
    node() {
        for (int i = 0; i < 20; i++) {
            par[i] = NULL;
        }
        sz = 0;
    }
};

node *t[1000005];

void Init() {
    t[0] = new node();
}

int nxt = 0;
void TypeLetter(char L) {
    ++nxt;
    if (!t[nxt]) {
        t[nxt] = new node();
    }
    t[nxt] -> cur = L;
    t[nxt] -> sz = t[nxt - 1] -> sz + 1;
    t[nxt] -> par[0] = t[nxt - 1];
    for (int i = 1; i < 20; i++) {
        if (t[nxt] -> par[i - 1]) {
            t[nxt] -> par[i] = (t[nxt] -> par[i - 1]) -> par[i - 1];
        }
    }
}
void UndoCommands(int U) {
    ++nxt;
    t[nxt] = t[nxt - U - 1];
}
char GetLetter(int P) {
    node *cur = t[nxt];
    int d = cur -> sz - P - 1;
    for (int i = 19; i >= 0; i--) {
        if (d & (1 << i)) {
            cur = cur -> par[i];
        }
    }
    return cur -> cur;
}
