#include <iostream>
#include <vector>

using namespace std;

void Merge(int* a, int l, int m, int r, int* buf) {
    memcpy(buf + l, a + l, (r - l) * sizeof(int));
    int pos1 = l, pos2 = m, cnt = l;
    while (pos1 < m && pos2 < r) {
        if (buf[pos1] < buf[pos2]) {
            a[cnt++] = buf[pos2++];
        } else {
            a[cnt++] = buf[pos1++];
        }
    }
    while (pos1 < m) {
        a[cnt++] = buf[pos1++];
    }
    while (pos2 < r) {
        a[cnt++] = buf[pos2++];
    }
}

void MergeSort(int* a, int l, int r, int* b) {
	if (l < r) {
		int m = (l + r) / 2;
		MergeSort(a, l, m, b);
		MergeSort(a, m + 1, r, b);
		Merge(a, l, m, r, b);
	}
}

const int MAXN = 25000;
int a[MAXN];
int b[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}

	MergeSort(a, 0, n - 1, b);
	for (int i = n - 1; i >= 0; --i) {
		printf("%d\n", a[i]);
	}
	return 0;
}