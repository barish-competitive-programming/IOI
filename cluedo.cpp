#include "grader.h"
#include "cluedo.h"

void Solve(){
    int a[4] = {0, 1, 1, 1};
    int res = Theory(a[1], a[2], a[3]);
    while (res > 0) {
        a[res]++;
        res = Theory(a[1], a[2], a[3]);
    }
    return;
}
