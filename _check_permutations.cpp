#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <functional>
#include <queue>
#include <iterator>

using namespace std;

vector<string> res1, res2;

void perm(string& s, int i) {
    if (i + 1 == s.size()) {
        res1.push_back(s);
        return;
    }
    for (int j = i; j < s.size(); ++j) {
        swap(s[i], s[j]);
        perm(s, i + 1);
        swap(s[i], s[j]);
    }
}

void permLex(string s) {
    if (s.empty())
        return;
    sort(s.begin(), s.end());
    while (1) {
        res2.push_back(s);
        int first = -1;
        for (int i = (int)s.size() - 2; i >= 0; --i)
            if (s[i] < s[i + 1]) {
                first = i;
                break;
            }
        if (first == -1)
            break;
        int second = first + 1;
        for (int i = second + 1; i < s.size(); ++i)
            if (s[first] < s[i] && s[i] < s[second])
                second = i;
        swap(s[first], s[second]);
        sort(s.begin() + first + 1, s.end());
    }
}

bool Test(string s) {
    res1.clear();
    res2.clear();
    {
        perm(s, 0);
        sort(res1.begin(), res1.end());
        res1.erase(unique(res1.begin(), res1.end()), res1.end());
        for (int i = 0; i < res1.size(); ++i)
            cout << res1[i] << endl;
    }
    {
        permLex(s);
        if (res1 != res2)
            return false;
        return true;
    }
}

int main()
{
    vector<string> test;
    test.push_back("");
    test.push_back("a");
    test.push_back("ab");
    test.push_back("bca");
    test.push_back("baabc");
    int ok = 0;
    for (int i = 0; i < test.size(); ++i)
        if (Test(test[i])) {
            ++ok;
            cerr << "Ok!\n";
        }
        else
            cerr << "Error!\n";
    if (ok == test.size())
        cerr << "Everything is OK!\n";
    else
        cerr << "Hm-m-m...\n";
    return 0;
}      
