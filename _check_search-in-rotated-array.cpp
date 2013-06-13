/*
   8 9 10 1 2 3 4 5 6 7
   l        m         r
			___________ ->sorted part
   
   5 6 7 8 9 10 1 2 3 4
   l       m          r
   _________->sorted part
   
   4 4 4 4 5 6 7 4
   l     m       r
  
*/

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 10 * 1000;

int Search(int a[], int l, int r, int key) {
    if (l > r)
        return -1;
    int m = (l + r) / 2;
    if (a[m] == key)
        return m;
    
    if (a[l] < a[m]) { // left part is sorted
        if (a[l] <= key && key <= a[m])
            return Search(a, l, m - 1, key);
        else
            return Search(a, m + 1, r, key);
    } else if (a[m] < a[r]) { // right part is sorted
        if (a[m] <= key && key <= a[r])
            return Search(a, m + 1, r, key);
        else
            return Search(a, l, m - 1, key);
    } else {
        int res = Search(a, l, m - 1, key);
        if (res == -1)
            return Search(a, m + 1, r, key);
        else
            return res;
    }
    return -1;
}

int Search(int a[], int n, int key) {
    return Search(a, 0, n - 1, key);
}

bool Test() {
    int a[MAXN];
    int b[MAXN];
    for (int t = 0; t < 100; ++t) {
        // building sorted shifted array
        for (int i = 0; i < MAXN; ++i)
            a[i] = rand() % MAXN;
        sort(a, a + MAXN);
        int st = rand() % MAXN;
        for (int i = 0; i < MAXN; ++i)
            b[i] = a[(st + i) % MAXN];

        // do searching
        for (int i = 0; i < MAXN; ++i) {
            if (a[Search(a, MAXN, a[i])] != a[i]) {
                cerr << "run# " << t << ", ind = " << i << endl;
                cerr << i << ' ' << a[i] << ' '<< a[Search(a, MAXN, a[i])] << endl;
                return false;
            }
        }

        // check for "-1"
        set<int> S;
        for (int i = 0; i < MAXN; ++i)
            S.insert(b[i]);
        for (int i = 0; i < 10; ++i) {
            int x = rand();
            while (S.find(x) != S.end())
                x = rand();
            if (Search(a, MAXN, x) != -1) {
                cerr << "Problem with -1 value!\n";
                return false;
            }
        }
    }

    return true;
}

int main() {
    if (Test())
        cerr << "Ok!\n";
    else
        cerr << "Error!\n";
    cerr << "Done!\n";
    return 0;
}
