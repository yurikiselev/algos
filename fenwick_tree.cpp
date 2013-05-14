#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

int a[MAXN + 1], b[MAXN + 1];

inline int Prev(int x) {
	return x & (x - 1);
}

inline int Next(int x) {
	return (x << 1) - Prev(x);
}

void Update(int pos, int val) {
	while (pos <= MAXN) {
		a[pos] += val;
		pos = Next(pos);
	}
}

int Sum(int l, int r) {
	int res = 0;
	while (r > 0) {
		res += a[r];
		r = Prev(r);
	}
	--l;
	while (l > 0) {
		res -= a[l];
		l = Prev(l);
	}
	return res;
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

void Update2(int pos, int key) {
	b[pos] += key;
}

int main() {
    for (int i = 0; i < MAXN; ++i) {
        int t = rand() & 1;
        if (t == 0) { // update
            int pos = GetId();
            int val = rand();
			if (rand() & 1) {
				val = -val;
			}
            Update(pos, val);
            Update2(pos, val);
		} else {
            int l = GetId();
            int r = GetId();
            if (l > r) {
                swap(l, r);
            }
            int sum1 = Sum(l, r);
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