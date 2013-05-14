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

const int MAXN = 10 * 100 * 1000;

int color[MAXN];
bool total[MAXN];

void Color(int v, int tl, int tr, int l, int r, int col) {
	if (l > r) {
		return;
	}

	if (total[v] == true) {
		total[v + v] = true;
		color[v + v] = color[v];
		total[v + v + 1] = true;
		color[v + v + 1] = color[v];
	}

	total[v] = false;
	if (tl == l && tr == r) {
		color[v] = col;
		total[v] = true;
	} else {
		int tm = (tl + tr) / 2;
		Color(v + v, tl, tm, l, min(r, tm), col);
		Color(v + v + 1, tm + 1, tr, max(l, tm + 1), r, col);
	}
}

int Ask(int v, int tl, int tr, int x) {
	if (total[v])
		return color[v];

	int tm = (tl + tr) / 2;
	if (x <= tm)
		Ask(v + v, tl, tm, x);
	else
		Ask(v + v + 1, tm + 1, tr, x);
}

void Solve() {
	int n = 10;
	Color(1, 1, 10, 1, 10, 0);
	Color(1, 1, 10, 3, 6, 2);
	Color(1, 1, 10, 1, 3, 1);
	Color(1, 1, 10, 2, 7, 4);
	Color(1, 1, 10, 9, 10, 3);
	Color(1, 1, 10, 4, 9, 7);
	Color(1, 1, 10, 5, 5, 8);
	Color(1, 1, 10, 7, 8, 10);
	for (int i = 1; i <= 10; ++i)
		cout << Ask(1, 1, 10, i) << ' ';
	//1 4 4 7 8 7 10 10 7 3 
}

int main()
{
	//initfiles();
	Solve();
	return 0;
}
