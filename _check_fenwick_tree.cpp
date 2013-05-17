#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 10 * 1000;
const int MAX_VAL = 10 * 1000;

int a[MAX_N + 1], b[MAX_N];

inline int Prev(int x) {
    return x & (x - 1);
}

inline int Next(int x) {
    return (x << 1) - Prev(x);
}

void UpdateStupid(int pos, int val) {
    b[pos] += val;
}

void UpdateFenwick(int pos, int val) {
    while (pos <= MAX_N) {
        a[pos] += val;
        pos = Next(pos);
    }
}

void Update(int pos, int val) {
    UpdateStupid(pos, val);
    UpdateFenwick(pos + 1, val);
}

int RequestStupid(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; ++i)
        res += b[i];
    return res;
}

int RequestFenwick(int l, int r) {
    int res = 0;
    while (r) {
        res += a[r];
        r = Prev(r);
    }
    --l;
    while (l) {
        res -= a[l];
        l = Prev(l);
    }
    return res;
}

bool Request(int l, int r) {
    if (l > r)
        swap(l, r);
    return RequestStupid(l, r) == RequestFenwick(l + 1, r + 1);
}

void Cleanup() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
}

int GetPos() {
    return rand() % MAX_N;
}

int GetVal() {
    int res = rand() % MAX_VAL;
    return rand() & 1 ? res : -res;
}

bool Test() {
    Cleanup();
    for (int i = 0; i < 10 * 1000; ++i) {
        if (rand() & 1) { // update
            int val = GetVal();
            int pos = GetPos();
            Update(pos, val);
        } else { // request
            int l = GetPos();
            int r = GetPos();
            if (!Request(l, r)) {
                cerr << i << " - bad!\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
