#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 10000;

void Merge(int* a, int l, int m, int r, int* buf) {
    //memcpy(buf + l, a + l, (r - l) * sizeof(a[0]));
    for (int i = l; i < r; ++i)
        buf[i] = a[i];
    int pos1 = l;
    int pos2 = m;
    int cnt = l;
    while (pos1 < m && pos2 < r)
        if (buf[pos1] < buf[pos2])
            a[cnt++] = buf[pos1++];
        else 
            a[cnt++] = buf[pos2++];
    while (pos1 < m)
        a[cnt++] = buf[pos1++];
    while (pos2 < r) 
        a[cnt++] = buf[pos2++];
}

void MergeSort(int* a, int l, int r, int* buf) {
    if (l + 1 >= r)
        return;
    int m = (l + r) / 2;
    MergeSort(a, l, m, buf);
    MergeSort(a, m, r, buf);
    Merge(a, l, m, r, buf);
}

bool Test() {
    int a[MAXN];
    int b[MAXN];
    int buf[MAXN];
    for (int i = 0; i < MAXN; ++i)
        a[i] = b[i] = rand() % MAXN;

    sort(a, a + MAXN);
    MergeSort(b, 0, MAXN, buf);

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
