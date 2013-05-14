#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int INF = 100 * 1000 * 1000;

int main() {
    int a[MAXN];
    int n = 10;
    for (int i = 0; i < 10; ++i) {
        a[i] = rand() % 10;
        printf("%d ", a[i]);
    }
    printf("\n");

    int d[MAXN];
    d[0] = -INF;
    for (int i = 1; i <= n; ++i)
        d[i] = INF;

    for (int i = 0; i < n; i++) {
        int l = 0, r = n;
        int j = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (d[m] <= a[i]) {
                l = m + 1;
            } else {
                j = m;
                r = m - 1;
            }
        }
        std::cerr << "j = " << j << endl;
        if (d[j - 1] < a[i] && a[i] < d[j])
            d[j] = a[i];
    }

    for (int i = 0; i < n; ++i) {
        printf("d[%d] = %d\n", i, d[i]);
    }
    return 0;
}
