#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

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

void Solve() {
	vector<int> a;
	a.push_back(10);
	a.push_back(10);
	a.push_back(10);
	a.push_back(20);
	a.push_back(20);
	a.push_back(20);
	a.push_back(20);
	a.push_back(10);
	a.push_back(30);
	a.push_back(10);
	a.push_back(10);

	cout << FindMajority(a) << endl;
}

int main()
{
	initfiles();
	Solve();
	return 0;
}
