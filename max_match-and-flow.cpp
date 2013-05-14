#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100;

struct TEdge {
    int to;
    int flow;
    int cap;
};

TEdge edges[MAXN * MAXN];
int cntE;
vector<int> newG[MAXN * 2 + 2];

int n, m, S, T;
bool mark[MAXN * 2 + 2];
int res[MAXN];
vector<int> g[MAXN];
int a[MAXN][MAXN];

void AddE(int a, int b, int cap) {
    TEdge ed;
    ed.to = b;
    ed.flow = 0;
    ed.cap = cap;
    edges[cntE] = ed;
    newG[a].push_back(cntE++);
    
    ed.to = a;
    ed.flow = 0;
    ed.cap = 0;
    edges[cntE] = ed;
    newG[b].push_back(cntE++);
}

void BuildGraph() {
    cntE = 0;
    S = 2 * n;
    T = S + 1;
    for (int i = 0; i < n; ++i) {
        AddE(S, i, 1);
        AddE(n + i, T, 1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            int v = i;
            int u = g[i][j];
            AddE(v, n + u, 1);
        }
    }
}

bool dfs(int v) {
    mark[v] = true;
    if (v == T) {
        return true;
    }
    for (int i = 0; i < newG[v].size(); ++i) {
        int edgeId = newG[v][i];
        int u = edges[edgeId].to;
        if (!mark[u] && edges[edgeId].cap > edges[edgeId].flow && dfs(u)) {
            edges[edgeId].flow++;
            edges[edgeId ^ 1].flow--;
            return true;
        }
    }
    return false;
}

int MaxFlow() {
    BuildGraph();
    int ans = 0;
    while (1) {
        memset(mark, 0, sizeof(mark));
        if (!dfs(S)) {
            break;
        }
        ++ans;
        while (1) {
            mark[S] = mark[T] = 0;
            if (!dfs(S)) {
                break;
            }
            ++ans;
        }
    }
    return ans / 2;
}

bool TryKuhn(int v) {
    if (mark[v]) 
        return false;
    mark[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if (res[u] == -1 || TryKuhn(res[u])) {
            res[u] = v;
            return true;
        }
    }
    return false;
}

int MaxMatch() {
    memset(res, -1, sizeof(res));

    for (int i = 0; i < MAXN; ++i) {
        memset(mark, false, sizeof(mark));
        TryKuhn(i);
    }

    int ans = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (res[i] != -1) {
            ++ans;
        }
    }
    return ans / 2;
}

void Clean() {
    n = m = S = T = 0;
    cntE = 0;
    for (int i = 0; i < MAXN * 2 + 2; ++i) {
        newG[i].clear();
    }
    for (int i = 0; i < MAXN; ++i) {
        g[i].clear();
    }
    memset(a, 0, sizeof(a));
    memset(res, -1, sizeof(res));
    memset(mark, 0, sizeof(mark));
}

void Generate() {
    n = rand() % MAXN + 1;
    m = n * n / 30;
    for (int i = 0; i < m; ++i) {
        int x = rand() % n;
        int y = rand() % n;
        a[x][y] = a[y][x] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) {
                g[i].push_back(j);
            }
        }
    }
}

int main() {
/*
Input:
10 7
2 3
2 8
5 4
5 6
6 7
9 8
8 10

Output:
1 0
2 3
3 2
4 5
5 4
6 7
7 6
// дальше опционально
8 9
9 8
10 0
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
*/

    for (int i = 0; i < 10; ++i) {
        Clean();
        Generate();
        int maxMatch = MaxMatch();
        int maxFlow = MaxFlow();
        if (maxMatch != maxFlow) {
            cerr << "We are in trouble!\n";
            cerr << "\tMaxMatch = " << maxMatch << ", MaxFlow = " << maxFlow << endl;
        } else {
            cerr << "Everything is OK!\n";
        }
    }

    return 0;
}
