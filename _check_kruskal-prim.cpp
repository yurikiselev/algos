#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10 * 1000;
const int MAXE = 5 * MAXN;
const int MAX_COST = 10 * 1000;
const int INF = 100 * 1000 * 1000;

struct TEdge {
    int from;
    int to;
    int cost;
    TEdge(int a, int b, int c)
        : from(a)
        , to(b)
        , cost(c)
    {}
};

bool operator<(TEdge l, TEdge r) {
    return l.cost < r.cost;
}

vector<TEdge> edges;
vector<int> g[MAXN];
int rank[MAXN], par[MAXN];

void Clean() {
    edges.clear();
    for (int i = 0; i < MAXN; ++i)
        g[i].clear();
}

void AddE(int x, int y, int cost) {
    g[x].push_back(edges.size());
    edges.push_back(TEdge(x, y, cost));
    g[y].push_back(edges.size());
    edges.push_back(TEdge(y, x, cost));
}

void Generate() {
    for (int i = 0; i < MAXE; ++i) {
        int x = rand() % MAXN;
        int y = rand() % MAXN;
        int cost = rand() % MAX_COST;
        AddE(x, y, cost);
    }

    // This part is here to garantee exact 1 connected component
    // FIXME try to delete this!
    int id = rand() % MAXN;
    for (int i = 0; i < MAXN; ++i) {
        int cost = rand() % MAX_COST;
        AddE(id, i, cost);
    }
}

void CleanKruskal() {
    for (int i = 0; i < MAXN; ++i) {
        rank[i] = 0;
        par[i] = i;
    }
}

int GetPar(int x) {
    if (x != par[x])
        par[x] = GetPar(par[x]);
    return par[x];
}

bool Union(int x, int y) {
    x = GetPar(x);
    y = GetPar(y);
    if (x == y)
        return false;
    if (rank[x] > rank[y])
        par[y] = x;
    else {
        par[x] = y;
        if (rank[x] == rank[y])
            ++rank[y];
    }
    return true;
}

int Kruskal() {
    CleanKruskal();
    vector<TEdge> sortedE = edges;
    sort(sortedE.begin(), sortedE.end());

    int res = 0;
    for (int i = 0; i < sortedE.size(); ++i) {
        int x = sortedE[i].from;
        int y = sortedE[i].to;
        if (Union(x, y)) {
            res += sortedE[i].cost;
        }
    }
    return res;
}

int Prim() {
    int res = 0;
    vector<int> cost(MAXN, INF);
    vector<bool> mark(MAXN, false);
    cost[0] = 0;
    set< pair<int, int> > Q;
    Q.insert(make_pair(cost[0], 0));
    for (int i = 0; i < MAXN; ++i) {
        if (Q.empty())
            throw "There's at least two components!";
        int from = Q.begin()->second;
        Q.erase(Q.begin());
        mark[from] = true;
        res += cost[from];
        for (int i = 0; i < g[from].size(); ++i) {
            int to = edges[g[from][i]].to;
            int add = edges[g[from][i]].cost;
            if (!mark[to] && cost[to] > add) {
                Q.erase(make_pair(cost[to], to));
                cost[to] = add;
                Q.insert(make_pair(cost[to], to));
            }
        }
    }
    return res;
}

bool Test() {
    Clean();
    Generate();
    int kr = Kruskal();
    int pr = Prim();
    cerr << "\t" << kr << ' ' << pr << endl;
    return kr == pr;
}

int main() {
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
    return 0;
}
