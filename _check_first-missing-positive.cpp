#include <iostream>
#include <algorithm>
#include <limits>
#include <set>

using namespace std;

const int MAXN = 10000;

int a[MAXN];

int FirstMissingPositiv1(int* a, int n) {
    set<int> S;
    for (int i = 0; i < n; ++i)
        S.insert(a[i]);
    for (int i = 1; i <= n + 1; ++i)
        if (S.find(i) == S.end())
            return i;
    return numeric_limits<int>::max(); // just in case
}

int FirstMissingPositiv2(int* a, int n) {
    //segregate
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (a[i] > 0)
                a[cnt++] = a[i];
        n = cnt;
    }

    for (int i = 0; i < n; ++i) {
        int x = abs(a[i]) - 1; // !!!
        if (x <= n && a[x] > 0)
            a[x] = -abs(a[x]);
    }
    for (int i = 0; i < n; ++i)
        if (a[i] > 0)
            return i + 1;
    return n + 1;
}

bool Test() {
    for (int i = 0; i < MAXN; ++i) {
        int x = rand() % (2 * MAXN) + 1;
        if (rand() % 4 == 0)
            x %= 500;
        if (rand() & 1)
            x = -x;
        a[i] = x;
    }

    int first1 = FirstMissingPositiv1(a, MAXN);
    int first2 = FirstMissingPositiv2(a, MAXN);
    cerr << "\t" << first1 << ' ' << first2 << endl;
    return first1 == first2;
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
