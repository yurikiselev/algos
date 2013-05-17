#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 10 * 1000;

int a[MAXN];
int M[MAXN][20];

void Prebuild() {
    for (int i = 0; i < MAXN; ++i) {
        M[i][0] = i;
    }
    for (int len = 1; (1 << len) <= MAXN; ++len) {
        for (int pos = 0; pos + (1 << len) <= MAXN; ++pos) {
            if (a[M[pos][len - 1]] > a[M[pos + (1 << (len - 1))][len - 1]]) {
                M[pos][len] = M[pos][len - 1];
            } else {
                M[pos][len] = M[pos + (1 << (len - 1))][len - 1];
            }
        }
    }
}

int Max(int i, int j) {
    int len = log(1. * j - i + 1) / log(2.);
    if (a[M[i][len]] > a[M[j - (1 << len) + 1][len]]) {
        return a[M[i][len]];
    }
    return a[M[j - (1 << len) + 1][len]];
}

int StupidoMax(int l, int r) {
    int ans = a[l++];
    while (l <= r) {
        ans = max(ans, a[l++]);
    }
    return ans;
}

bool Test() {
    for (int i = 0; i < MAXN; ++i) {
        a[i] = rand() % 1000;
    }

    Prebuild();

    for (int i = 0; i < MAXN; ++i) {
        int x = rand() % MAXN;
        int y = rand() % MAXN;
        if (x > y) {
            swap(x, y);
        }
        if (StupidoMax(x, y) != Max(x, y)) {
            cerr << "Error - " << i << " step\n";
            cerr << "(x, y) = (" << x << ", " << y << ")\n";
            cerr << "StupidoMax = " << StupidoMax(x, y) << ", Max = " << Max(x, y) << endl;
            return false;
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
