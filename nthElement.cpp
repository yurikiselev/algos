#include <iostream>
#include <algorithm>

using namespace std;

const int TEST_NUM = 1000;
const int MAXN = 100;

int Sort(int *a, int l, int r) {
	int m = l + rand() % (r - l);
	swap(a[l], a[m]);
	int i = l;
	int j = i + 1;
	while (j < r) {
		if (a[i] > a[j]) {
			swap(a[i], a[j]);
			swap(a[i + 1], a[j]);
			++i;
		}
		++j;
	}
	return i;
}

void QSort(int *a, int l, int r) {
	if (l + 1 >= r) {
		return;
	}
	int m = Sort(a, l, r);
	QSort(a, l, m);
	QSort(a, m + 1, r);
}

int kthElement(int *a, int l, int r, int n) {
	if (l + 1 == r) {
		return a[l];
	}
	int m = Sort(a, l, r);
	if (m == n) {
		return a[m];
	}
	if (n < m) {
		return kthElement(a, l, m, n);
	} else {
		return kthElement(a, m, r, n);
	}
}

int a[MAXN];

int main() {
	for (int i = 0; i < TEST_NUM; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			a[j] = rand();
		}
		QSort(a, 0, MAXN);
		for (int j = 1; j < MAXN; ++j) {
			if (a[j] < a[j - 1]) {
				cerr << "Sorting error!\n";
				return 0;
			}
		}
	}
	cout << "Sorting is fine!\n";

	for (int i = 0; i < TEST_NUM; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			a[j] = j;
		}
		random_shuffle(a, a + MAXN);
		int n = rand() % MAXN;
		if (kthElement(a, 0, MAXN, n) != n) {
			cerr << "kthElement error\n";
			return 0;
		}
	}
	cout << "kthElement is fine!\n";
	return 0;
}