#pragma comment(linker, "/STACK:16777216")
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int root;
vector<int> g[40000];
int E[3 * 40000], L[3 * 40000], H[3 * 40000];
int M[3 * 40000][17];
int cnt;
bool mark[3 * 40000];

void In() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (y == -1) {
			root = x;
		} else {
			g[y].push_back(x);
		}
	}
}

void Process(int *a, int M[][17], int n) {
	for (int i = 0; i < n; ++i) {
		M[i][0] = i;
	}
	for (int len = 1; (1 << len) <= n; ++len) {
		for (int pos = 0; pos + (1 << len) <= n; ++pos) {
			if (a[M[pos][len - 1]] < a[M[pos + (1 << (len - 1))][len - 1]]) {
				M[pos][len] = M[pos][len - 1];
			} else {
				M[pos][len] = M[pos + (1 << (len - 1))][len - 1];
			}
		}
	}
}

int FindMin(int *a, int M[][17], int i, int j) {
	if (i > j) {
		swap(i, j);
	}
	int len = log(1. * j - i + 1) / log(2.);
	if (a[M[i][len]] < a[M[j - (1 << len) + 1][len]]) {
		return M[i][len];
	} else {
		return M[j - (1 << len) + 1][len];
	}
}

void dfs(int v, int level) {
	mark[v] = true;
	E[cnt] = v;
	H[v] = cnt;
	L[cnt++] = level;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int u = g[v][i];
		if (!mark[u]) {
			dfs(u, level + 1);
			E[cnt] = v;
			L[cnt++] = level;
		}
	}
}

int lca(int x, int y) {
	if (x > y) {
		swap(x, y);
	}
	x = H[x];
	y = H[y];
	int mi = FindMin(L, M, x, y);
	return E[mi];
}

void Solve() {
	cnt = 0;
	dfs(root, 0);
	Process(L, M, cnt);

	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		int tmp = lca(x, y);
		if (tmp == x) {
			printf("1\n");
		} else {
			if (tmp == y) {
				printf("2\n");
			} else {
				printf("0\n");
			}
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	In();
	Solve();
	return 0;
}