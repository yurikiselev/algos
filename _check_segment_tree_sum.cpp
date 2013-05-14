#pragma comment(linker, STACK16777216)
#include <iostream>

using namespace std;

const int MAXN = 1000;

int a[MAXN + 1], b[MAXN + 1];
int sum[(MAXN + 1) * 4];
int add[(MAXN + 1) * 4];

void Update(int v, int tl, int tr, int l, int r, int val) {
    if (l > r)
        return;
    sum[v] += (r - l + 1) * val;
    if (tl == l && tr == r)
        add[v] += val;
    else {
        int tm = (tl + tr) / 2;
        Update(v + v, tl, tm, l, min(r, tm), val);
        Update(v + v + 1, tm + 1, tr, max(l, tm + 1), r, val);
    }
}

int Sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return sum[v];
    int tm = (tl + tr) / 2;
    return add[v] * (r - l + 1) + Sum(v + v, tl, tm, l, min(r, tm)) +
        Sum(v + v + 1, tm + 1, tr, max(l, tm + 1), r);
}

inline int GetId() {
    return rand() % MAXN + 1;
}

int Sum2(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; ++i) {
        res += b[i];
    }
    return res;
}

void Update2(int l, int r, int key) {
    for (int i = l; i <= r; ++i) {
        b[i] += key;
    }
}

int main() {
    for (int i = 1; i <= MAXN; ++i) {
        a[i] = b[i] = rand() % MAXN;
    }
    
    for (int i = 1; i <= MAXN; ++i) {
        Update(1, 1, MAXN, i, i, a[i]);
    }
    
    for (int i = 0; i < MAXN; ++i) {
        int t = rand() & 1;
        if (t == 0) {  // update
            int l = GetId();
            int r = GetId();
            if (l > r) {
                swap(l, r);
            }
            int val = rand();
            if (rand() % 2 == 0) {
                val = -val;
            }
            Update(1, 1, MAXN, l, r, val);
            Update2(l, r, val);
        } else {
            int l = GetId();
            int r = GetId();
            if (l > r) {
                swap(l, r);
            }
            int sum1 = Sum(1, 1, MAXN, l, r);
            int sum2 = Sum2(l, r);
            if (sum1 != sum2) {
                cerr << "error!\n";
                return 0;
            }
        }
    }
    cerr << "Everything is OK!\n";
    return 0;
}
