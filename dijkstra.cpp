#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1000;
const int INF = 1000 * 1000 * 1000;

struct TEdge {
	int a, b, cost;
	TEdge(int x = 0, int y = 0, int c = 0)
		: a(x)
		, b(y)
		, cost(c)
	{
	}
};

int n, m;
TEdge edges[MAXN];
vector<int> g[MAXN];
int cnt;
int d[MAXN];
set< pair<int, int> > S;

void Add(int a, int b, int c) {
	edges[cnt] = TEdge(a, b, c);
	g[a].push_back(cnt++);
	edges[cnt] = TEdge(b, a, c);
	g[b].push_back(cnt++);
}

void In() {
	cnt = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		--x;
		--y;
		Add(x, y, d);
	}
}

void Solve() {
	for (int i = 0; i < n; ++i) {
		d[i] = INF;
	}
	int st = 0;
	d[st] = 0;
	S.insert(make_pair(d[st], st));
	while (!S.empty()) {
		pair<int, int> tmpP = *S.begin();
		S.erase(S.begin());
		int v = tmpP.second;
		int curD = tmpP.first;
		for (size_t i = 0; i < g[v].size(); ++i) {
			int u = edges[g[v][i]].b;
			if (d[u] > d[v] + edges[g[v][i]].cost) {
				S.erase(make_pair(d[u], u));
				d[u] = d[v] + edges[g[v][i]].cost;
				S.insert(make_pair(d[u], u));
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		printf("%d to vertex #%d\n", d[i], i + 1);
	}
}

int main() {
	/*
	input:				output:
	11 12				0 to vertex #1
	1 2 20				17 to vertex #2
	1 9 14				16 to vertex #3
	9 2 3				25 to vertex #4
	4 5 15				40 to vertex #5
	11 4 7				1016 to vertex #6
	6 3 1000			18 to vertex #7
	11 2 1				19 to vertex #8
	11 3 2				14 to vertex #9
	3 9 2				1000000000 to vertex #10
	9 8 5				18 to vertex #11
	3 7 2
	8 7 2
	*/
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	In();
	Solve();
	return 0;
}