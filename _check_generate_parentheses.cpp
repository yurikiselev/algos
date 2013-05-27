#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<string> res;

	void Generate(int remLeft, int remRight, string& s, int cnt) {
		if (remLeft == 0 && remRight == 0) {
			res.push_back(s);
			return;
		}
		if (remLeft) {
			s[cnt] = '(';
			Generate(remLeft - 1, remRight, s, cnt + 1);
		}
		if (remRight > remLeft) {
			s[cnt] = ')';
			Generate(remLeft, remRight - 1, s, cnt + 1);
		}
	}
    vector<string> generateParenthesis(int n) {
		res.clear();
		string tmp(2 * n, '.');
		Generate(n, n, tmp, 0);
		return res;
    }
};

void generate(int len, vector<string>& res) {
	string s = string(len, '(') + string(len, ')');
	int n = (int)s.size();
	while (1) {
        res.push_back(s);
		bool next = false;
		string res;
		for (int i = n - 1, depth = 0; i >= 0; --i) {
			if (s[i] == ')') {
				++depth;
			} else {
				--depth;
			}
			if (s[i] == '(' && depth > 0) {
				--depth;
				int open = (n - i - 1 - depth) / 2;
				int close = n - i - 1 - open;
				s = s.substr(0, i) + ")" + string(open, '(') + string(close, ')');
				next = true;
				break;
			}
		}
		if (!next) {
			break;
		}
	}
}

bool Test(int n) {
    Solution sol;
    sol.generateParenthesis(n);
    vector<string> v;
    generate(n, v);
    cerr << "\t" << v.size() << ' ' << sol.res.size() << endl;
    return v == sol.res;
}

int main()
{
    for (int i = 0; i < 10; ++i)
        if (Test(i))
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
