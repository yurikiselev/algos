// QSORT
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

int a[MAXN];

int Sort(int l, int r) {
	//int m = l + (r - l) / 2; // use rand here TODO
	int m = l + rand() % (r - l);
	swap(a[l], a[m]);
	int i = l;
	int j = i + 1;
	while (j < r) {
		if (a[j] < a[i]) {
			swap(a[i], a[j]);
			swap(a[i + 1], a[j]);
			++i;
		}
		++j;
	}
	return i;
}

void QSort(int l, int r) {
	if (l >= r) {
		return;
	}
	int m = Sort(l, r);
	QSort(l, m);
	QSort(m + 1, r);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	QSort(0, n);
	for (int i = n - 1; i >= 0; --i) {
		printf("%d\n", a[i]);
	}
	return 0;
}