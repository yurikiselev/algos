#include <iostream>
#include <string>
using namespace std;

const int MAXN = 500;

void GetPref(const string& s, int* p) {
    p[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        p[i] = j;
    }
}

void GetStupidoPref(const string& s, int* p) {
    int n = (int) s.length();
    for (int i = 0; i < n; ++i)
        for (int k = 0; k <= i; ++k)
            if (s.substr(0, k) == s.substr(i - k + 1, k))
                p[i] = k;
}

void Generate(string& s) {
    s.clear();
    for (int i = 0; i < MAXN; ++i)
        s.push_back('a' + rand() % 2);
}

bool Test() {
    string s;
    Generate(s);
    int p[MAXN];
    GetPref(s, p);
    int pStup[MAXN];
    GetStupidoPref(s, pStup);
    int maxP = 0;
    for (int i = 0; i < MAXN; ++i) {
        maxP = max(maxP, p[i]);
        if (p[i] != pStup[i])
            return false;
    }
    cerr << "\t Max pref function - " << maxP << endl;
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Erro!\n";
    cerr << "Done!\n";
    return 0;
}
