#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 10000;

bool mark[MAXN];
vector<int> g[MAXN];

void dfs(int v, vector<int>& comp) {
    mark[v] = true;
    comp.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if (!mark[u]) {
            dfs(u, comp);
        }
    }
}

vector< vector<int> > GetDfsComps() {
    memset(mark, 0, sizeof(mark));
    vector< vector<int> > res;
    for (int i = 0; i < MAXN; ++i) {
        if (!mark[i]) {
            vector<int> v;
            dfs(i, v);
            res.push_back(v);
        }
    }
    return res;
}

vector< vector<int> > GetBfsComps() {
    memset(mark, 0, sizeof(mark));
    vector< vector<int> > res;
    for (int i = 0; i < MAXN; ++i) {
        if (mark[i]) {
            continue;
        }
        queue<int> q;
        q.push(i);
        mark[i] = true;
        vector<int> comp;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            comp.push_back(v);
            for (int j = 0; j < g[v].size(); ++j) {
                int u = g[v][j];
                if (!mark[u]) {
                    q.push(u);
                    mark[u] = true;
                }
            }
        }
        res.push_back(comp);
    }
    return res;
}

void Normalize(vector< vector<int> >& v) {
    for (int i = 0; i < v.size(); ++i) {
        sort(v[i].begin(), v[i].end());
    }
    sort(v.begin(), v.end());
}

bool RunTest() {
    for (int i = 0; i < MAXN; ++i) {
        g[i].clear();
    }

    for (int i = 0; i < 2 * MAXN; ++i) {
        int x = rand() % MAXN;
        int y = rand() % MAXN;
        g[x].push_back(y);
    }
    vector< vector<int> > v1 = GetDfsComps();
    vector< vector<int> > v2 = GetBfsComps();
    Normalize(v1);
    Normalize(v2);
    return v1 == v2;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        if (!RunTest()) {
            printf("Error!\n");
        } else {
            printf("Ok!\n");
        }
    }
    return 0;
}
