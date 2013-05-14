#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

struct Term {
	int val; // value
	char op; // operation
	short pr; // priority
	bool isOp;
	Term(int x, char c, short p, bool is_op)
		: val(x)
		, op(c)
		, pr(p)
		, isOp(is_op)
	{
	}
};

typedef vector<Term> Expr;

int GetNum(const string& s, int& pos) {
	int res = 0;
	while (pos < s.size() && isdigit(s[pos])) {
		res = res * 10 + s[pos++] - '0';
	}
	return res;
}

Expr GetExpr(const string& s) {
	Expr res;
	stack<Term> st;
	int pos = 0;
	while (pos < s.size()) {
		if (isspace(s[pos])) {
			++pos;
			continue;
		}
		if (isdigit(s[pos])) {
			res.push_back(Term(GetNum(s, pos), '\0', 0, false));
			continue;
		}
		if (s[pos] == '(') {
			st.push(Term(0, s[pos], 1, true));
		}
		if (s[pos] == ')') {
			while (!st.empty() && st.top().op != '(') {
				res.push_back(st.top());
				st.pop();
			}
			st.pop(); // delete '('
		}
		if (s[pos] == '-' || s[pos] == '+') {
			while (!st.empty() && st.top().pr >= 2) {
				res.push_back(st.top());
				st.pop();
			}
			st.push(Term(0, s[pos], 2, true));
		}
		if (s[pos] == '*' || s[pos] == '/') {
			while (!st.empty() && st.top().pr >= 3) {
				res.push_back(st.top());
				st.pop();
			}
			st.push(Term(0, s[pos], 3, true));
		}
		++pos;
	}
	while (!st.empty()) {
		res.push_back(st.top());
		st.pop();
	}
	return res;
}

int Calculate(Expr exp) {
	vector<int> res;
	for (int i = 0; i < exp.size(); ++i) {
		if (!exp[i].isOp) {
			res.push_back(exp[i].val);
		} else {
			int b = res[res.size() - 1];
			int a = res[res.size() - 2];
			res.pop_back();
			res.pop_back();
			if (exp[i].op == '+')
				res.push_back(a + b);
			if (exp[i].op == '-')
				res.push_back(a - b);
			if (exp[i].op == '*')
				res.push_back(a * b);
			if (exp[i].op == '/')
				res.push_back(a / b);
		}
	}
	if (res.size() != 1) {
		cerr << "Error!\n";
	}
	return res.back();
}

int main()
{
	initfiles();

	string s;
	while (getline(cin, s, '\n')) {
		Expr exp = GetExpr(s);
		cout << Calculate(exp) << endl;
	}

	return 0;
}

/*
0
(99)
(99+(100))
2 + 2 * (10 + 4 / 2) / (3)
1/1*2
3/1/1/1/1/1/1/1*1*1*1/1*1/1*1*2
(1728/2/3*2+1728*2/3*2/3/2*3/2/2)*2

0
99
199
10
2
6
1728
*/