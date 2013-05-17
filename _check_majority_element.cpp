#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int FindMajority(const vector<int>& v) { 
     int cnt = 0, majId = 0;
     for (int i = 0; i < v.size() ; i++) {
        if (cnt == 0) {
            majId = i;
        }
        if(v[i] == v[majId]) 
           ++cnt;
        else 
           --cnt;
     }
     cnt = 0;
     for (int i = 0; i < v.size(); i++) {
          if (v[i] == v[majId]) {
                cnt++;
          }
	 }
     if (cnt > v.size() / 2) {
          return v[majId];
     }
     return -1;
}

bool Test() {
    int n = 10 * 1000 + rand() % 2;
    vector<int> v;
    int x = rand();
    for (int i = 0; i < n / 2 + 1; ++i)
        v.push_back(x);
    while (v.size() < n)
        v.push_back(rand());
    random_shuffle(v.begin(), v.end());
    return x = FindMajority(v);
}

int main()
{
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
