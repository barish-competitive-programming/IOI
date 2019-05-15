#include <bits/stdc++.h>
#include <ext/rope>
#include "grader.h"

using namespace __gnu_cxx;
using namespace std;

rope <char> v[1000006]; int nxt = 0;

void Init() {}

void TypeLetter(char L) {
    v[nxt + 1].insert(v[nxt + 1].mutable_begin(), v[nxt]);
    v[++nxt].push_back(L);
}
void UndoCommands(int U) {
    v[nxt + 1].insert(v[nxt + 1].mutable_begin(), v[nxt - U]);
    nxt++;
}
char GetLetter(int P) {
    return v[nxt][P];
}
