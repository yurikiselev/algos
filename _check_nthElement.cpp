#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

int Partition(int* a, int l, int r) {
    swap(a[l], a[(l + r) / 2]);
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

int kthElement(int* a, int l, int r, int n) {
	if (l + 1 == r) {
		return a[l];
	}
	int m = Partition(a, l, r);
	if (m == n) {
		return a[m];
	}
	if (n < m) {
		return kthElement(a, l, m, n);
	} else {
		return kthElement(a, m, r, n);
	}
}

bool Test() {
    int a[MAXN];
    int b[MAXN];
    for (int i = 0; i < MAXN; ++i)
        a[i] = b[i] = rand();
    sort(b, b + MAXN);
    for (int i = 0; i < MAXN; ++i) {
        random_shuffle(a, a + MAXN);
        if (kthElement(a, 0, MAXN, i) != b[i])
            return false;
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

/*
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
	cout << "kthElement is fine!\n";*/
	return 0;
}
