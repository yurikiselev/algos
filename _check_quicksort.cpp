#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 10000;

int Partition(int* a, int l, int r) {
    int m = l + rand() % (r - l + 1);
    swap(a[l], a[m]);
    int i = l;
    int j = i + 1;
    while (j <= r) {
        if (a[i] > a[j]) {
            swap(a[i], a[j]);
            swap(a[i + 1], a[j]);
            ++i;
        }
        ++j;
    }
    return i;
}

void QSort(int* a, int l, int r) {
    if (l >= r)
        return;
    int m = Partition(a, l, r);
    QSort(a, l, m - 1);
    QSort(a, m + 1, r);
}

bool Test() {
    int a[MAXN];
    int b[MAXN];
    for (int i = 0; i < MAXN; ++i)
        a[i] = b[i] = rand() % MAXN;
    sort(a, a + MAXN);
    QSort(b, 0, MAXN - 1);
    for (int i = 0; i < MAXN; ++i)
        if (a[i] != b[i])
            return false;
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
