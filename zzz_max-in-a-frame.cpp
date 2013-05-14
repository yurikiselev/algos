#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

void Find(const vector<int>& v, int k) {
	int n = v.size();
	if (k > n)
		k = n;
	deque<int> deq;
	for (int i = 0; i < k - 1; ++i) {
		while (!deq.empty() && v[deq.back()] < v[i])
			deq.pop_back();
		deq.push_back(i);
	}
	for (int i = k - 1; i < n; ++i) {
		while (!deq.empty() && v[deq.back()] < v[i])
			deq.pop_back();
		deq.push_back(i);
		printf("%d\n", v[deq.front()]);
		if (i - (k - 1) == deq.front())
			deq.pop_front();
	}
}

void In(vector<int>& v, int& k) {
	v.reserve(25 * 1000);
	scanf("%d", &k);
	int x;
	scanf("%d", &x);
	while (x != -1) {
		v.push_back(x);
		scanf("%d", &x);
	}
}

void Solve() {
	vector<int> v;
	int k;
	In(v, k);
	Find(v, k);
}

int main()
{
	initfiles();
	Solve();
	return 0;
}
