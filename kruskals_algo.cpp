#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int INF = 1000 * 1000 * 1000;

struct TEdge {
	int x, y, cost;
	TEdge(int X = 0, int Y = 0, int Cost = 0)
		: x(X)
		, y(Y)
		, cost(Cost)
	{
	}
	bool operator<(const TEdge &r) const {
		return this->cost < r.cost;
	}
};

int n, m;
TEdge edges[MAXN];
int cnt;
int p[MAXN];
int r[MAXN];

void In() {
	cnt = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		--x;
		--y;
		edges[cnt++] = TEdge(x, y, c);
	}
}

void Init(int n) {
	for (int i = 0; i < n; ++i) {
		p[i] = i;
		r[i] = 1;
	}
}

int FindSet(int x) {
	if (x == p[x]) {
		return x;
	}
	return p[x] = FindSet(p[x]);
}

void Union(int x, int y) {
	x = FindSet(x);
	y = FindSet(y);
	if (r[x] > r[y]) {
		p[y] = x;
	} else {
		p[x] = y;
		if (r[x] == r[y]) {
			++r[y];
		}
	}
}

void Solve() {
	Init(n);
	sort(edges, edges + cnt); // sort(edges[0], edges[cnt]); - не работает!!!
	for (int i = 0; i < cnt; ++i) {
		int x = edges[i].x;
		int y = edges[i].y;
		if (FindSet(x) != FindSet(y)) {
			Union(x, y);
			printf("%d %d\n", x + 1, y + 1);
		}
	}
}

int main() {
	/*
	input:			output:
	11 12			11 2
	1 2 20			11 3
	1 9 14			3 9
	9 2 3			3 7
	4 5 15			8 7
	11 4 7			11 4
	6 3 1000		1 9
	11 2 1			4 5
	11 3 2			6 3
	3 9 2
	9 8 5
	3 7 2
	8 7 2
	*/
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	In();
	Solve();
	return 0;
}