#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 10000;

void Sort(int* a, int n) {
    int low = 0;
    int mid = 0;
    int hi = n - 1;
    while (mid <= hi)
        if (a[mid] == 0)
            swap(a[mid++], a[low++]);
        else
            if (a[mid] == 1)
                ++mid;
            else // a[mid] == 2
                swap(a[mid], a[hi--]);
}

bool Test() {
    int a[MAXN], b[MAXN];
    for (int i = 0; i < MAXN; ++i)
        a[i] = b[i] = rand() % 3;

    sort(a, a + MAXN);
    Sort(b, MAXN);
    for (int i = 0; i < MAXN; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

int main() {
    for (int i = 0; i < 20; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
