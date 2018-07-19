#include "grader.h"
#include <bits/stdc++.h>

void initialize(int n) {

}

int d[2005];
int hasEdge(int u, int v) {
    return ++d[std::max(u, v)] == std::max(u, v);
}
