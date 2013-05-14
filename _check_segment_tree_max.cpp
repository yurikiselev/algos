#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 16 * 1024;
const int MAX_VAL = 100 * 1000;
const int INF = 100 * 1000 * 1000;

int a[MAXN + 1], b[MAXN + 1];
int maxi[(MAXN + 1) * 4];
int add[(MAXN + 1) * 4];

void Update(int v, int tl, int tr, int l, int r, int val) {
    if (l > r) {
        return;
    }
    if (tl == l && tr == r) {
        maxi[v] += val;
        add[v] += val;
    } else {
        int tm = (tl + tr) / 2;
        Update(v * 2, tl, tm, l, min(r, tm), val);
        Update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
        maxi[v] = max(maxi[v + v], maxi[v + v + 1]) + add[v];
    }
}

int Max(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        return -INF;
    }
    if (tl == l && tr == r) {
        return maxi[v];
    }
    int tm = (tl + tr) / 2;
    int res = -INF;
    res = max(res, Max(v + v, tl, tm, l, min(r, tm)));
    res = max(res, Max(v + v + 1, tm + 1, tr, max(l, tm + 1), r));
    if (res > -INF) {
        res += add[v];
    }
    return res;
}

inline int GetId() {
    return rand() % MAXN + 1;
}

int Max2(int l, int r) {
    int res = -INF;
    for (int i = l; i <= r; ++i) {
        res = max(res, b[i]);
    }
    return res;
}

void Update2(int l, int r, int key) {
    for (int i = l; i <= r; ++i) {
        b[i] += key;
    }
}

int GetVal() {
    return rand() % MAX_VAL;
}

int main() {
    //freopen("in.txt", "r", stdin);
    for (int i = 1; i <= MAXN; ++i) {
        a[i] = b[i] = GetVal();
    }

    for (int i = 1; i <= MAXN; ++i) {
        Update(1, 1, MAXN, i, i, a[i]);
    }

    for (int i = 0; i < MAXN; ++i) {
        int t = rand() & 1;
        if (t == 0) { // update
            int l = GetId();
            int r = GetId();
            if (l > r) {
                swap(l, r);
            }
            int val = GetVal();
            Update(1, 1, MAXN, l, r, val);
            Update2(l, r, val);
        } else {
            int l = GetId();
            int r = GetId();
            if (l > r) {
                swap(l, r);
            }
            int max1 = Max(1, 1, MAXN, l, r);
            int max2 = Max2(l, r);
            if (max1 != max2) {
                cerr << "error!\n";
                return 0;
            }
        }
    }
    cerr << "Everything is OK!\n";
    return 0;
}
