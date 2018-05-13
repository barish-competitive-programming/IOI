#include <bits/stdc++.h>

using namespace std;

const int maxN = 105;
const int maxM = 2005;

int N, M;
int R[maxN], W[maxM];
int res = 0, nCar, place[maxM];

set <int> slots; deque <int> wait;

void insert_car(int nCar) {
    if (slots.size() == 0) {
        wait.push_back(nCar);
        return;
    }
    res += R[*slots.begin()] * W[nCar];
    place[nCar] = *slots.begin();
    slots.erase(slots.begin());
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> R[i];
    }
    for (int i = 1; i <= M; i++) {
        cin >> W[i];
    }
    for (int i = 1; i <= N; i++) {
        slots.insert(i);
    }
    for (int i = 1; i <= M + M; i++) {
        cin >> nCar;
        if (nCar > 0) {
            insert_car(nCar);
        } else {
            nCar = -nCar;
            slots.insert(place[nCar]);
            if (wait.size() > 0) {
                insert_car(wait[0]);
                wait.pop_front();
            }
        }
    }
    cout << res << endl;
    return 0;
}
