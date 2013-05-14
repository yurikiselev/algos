#include <cstdio>

using namespace std;

const int MAXN = 100;
const int INF = 1000 * 1000 * 1000;

int n, m;
int a[MAXN][MAXN];

void In() {
	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			a[i][j] = INF;
		}
		a[i][i] = 0; // This is important!!!
	}

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		int x, y, cost;
		scanf("%d%d%d", &x, &y, &cost);
		--x;
		--y;
		a[x][y] = a[y][x] = cost;
	}
}

void Solve() {
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (a[i][k] < INF && a[k][j] < INF && a[i][j] > a[i][k] + a[k][j]) {
					a[i][j] = a[i][k] + a[k][j];
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (a[i][j] < INF) {	
				printf("%d\t", a[i][j]);
			} else {
				printf("inf\t");
			}
		}
		printf("\n");
	}
}

int main() {
	/*
	input:			output:
	11 12			0	17	16	25	40	1016	18	19	14	inf	18	
	1 2 20			17	0	3	8	23	1003	5	8	3	inf	1	
	1 9 14			16	3	0	9	24	1000	2	7	2	inf	2	
	9 2 3			25	8	9	0	15	1009	11	16	11	inf	7	
	4 5 15			40	23	24	15	0	1024	26	31	26	inf	22	
	11 4 7			1016	1003	1000	1009	1024	0	1002	1007	1002	inf	1002
	6 3 1000		18	5	2	11	26	1002	0	9	4	inf	4	
	11 2 1			19	8	7	16	31	1007	9	0	5	inf	9	
	11 3 2			14	3	2	11	26	1002	4	5	0	inf	4	
	3 9 2			inf	inf	inf	inf	inf	inf	inf	inf	inf	0	inf	
	9 8 5			18	1	2	7	22	1002	4	9	4	inf	0	
	3 7 2			
	8 7 2
	*/
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	In();
	Solve();
	return 0;
}