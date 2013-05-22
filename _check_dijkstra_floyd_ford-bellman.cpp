#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100;
const int MAXE = 5 * MAXN;
const int MAX_COST = 10 * 1000;
const int INF = 100 * 1000 * 1000;

struct Edge {
    int to;
    int cost;
    Edge(int x, int c)
        : to(x)
        , cost(c)
    {};
};

struct FullEdge {
    int a, b;
    int cost;
    FullEdge(int x, int y, int c)
        : a(x)
        , b(y)
        , cost(c)
    {}
};

int a[MAXN][MAXN];
int d[MAXN][MAXN];
int fb[MAXN][MAXN] ;
vector<Edge> g[MAXN];
vector<FullEdge> edges;

void Clean() {
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            a[i][j] = d[i][j] = fb[i][j] = INF;
    for (int i = 0; i < MAXN; ++i)
        g[i].clear();
    edges.clear();
}

void AddE(int x, int y, int cost) {
    a[x][y] = a[y][x] = min(a[x][y], cost);
    g[x].push_back(Edge(y, cost));
    g[y].push_back(Edge(x, cost));
    edges.push_back(FullEdge(x, y, cost));
}

void Generage() {
    for (int i = 0; i < MAXE; ++i) {
        int x = rand() % MAXN;
        int y = rand() % MAXN;
        while (x == y)
            y = rand() % MAXN;
        int cost = rand() % MAX_COST;
        AddE(x, y, cost);
    }
}

void Floyd() {
    for (int k = 0; k < MAXN; ++k)
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    for (int i = 0; i < MAXN; ++i)
        a[i][i] = 0;
}

void Dijkstra(int st, int* d) {
    d[st] = 0;
    set< pair<int, int> > Q;
    Q.insert(make_pair(d[st], st));
    while (!Q.empty()) {
        int v = Q.begin()->second;
        Q.erase(Q.begin());
        for (size_t i = 0; i < g[v].size(); ++i) {
            int u = g[v][i].to;
            int add = g[v][i].cost;
            if (d[u] > d[v] + add) {
                Q.erase(make_pair(d[u], u));
                d[u] = d[v] + add;
                Q.insert(make_pair(d[u], u));
            }
        }
    }
}

void Dijkstra() {
    for (int i = 0; i < MAXN; ++i)
        Dijkstra(i, d[i]);
}

void FordBellman(int st, int* d) {
    d[st] = 0;
    for (int t = 0; t < MAXN; ++t) {
        for (size_t i = 0; i < edges.size(); ++i) {
            int a = edges[i].a;
            int b = edges[i].b;
            int add = edges[i].cost;
            d[a] = min(d[a], d[b] + add);
            d[b] = min(d[b], d[a] + add);
        }
    }
}

void FordBellman() {
    for (int i = 0; i < MAXN; ++i)
        FordBellman(i, fb[i]);
}

bool Test() {
    Clean();
    Generage();
    Floyd();
    Dijkstra();
    FordBellman();
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            if (a[i][j] != d[i][j] || a[i][j] != fb[i][j]) {
                printf("err (%d, %d), cost1 - %d, cost2 - %d\n, cost3 - %d", i, j, a[i][j], d[i][j], fb[i][j]);
                return false;
            }
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i) 
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error\n";
    cerr << "Done!\n";
	return 0;
}
