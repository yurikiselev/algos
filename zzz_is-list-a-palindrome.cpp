#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

bool IsPal(const char* s) {
	const char* slow = s;
	const char* fast = s;
	stack<char> st;
	while (*fast != '\0' && *(fast + 1) != '\0') {
		st.push(*slow);
		slow += 1;
		fast += 2;
	}
	if (*fast != '\0')
		++slow;
	while (*slow != 0) {
		if (*slow != st.top())
			return false;
		++slow;
		st.pop();
	}
	return true;
}

void Test(const char* s, bool isPal) {
	printf("%6s ", s);
	if (isPal != IsPal(s))
		cout << "ERROR!\n";
	else
		if (isPal)
			cout << "is a palindrome\n";
		else
			cout << "is NOT a palindrome\n";
}

void Solve() {
	Test("", 1);
	Test("a", 1);
	Test("ab", 0);
	Test("aa", 1);
	Test("abc", 0);
	Test("aba", 1);
	Test("abcd", 0);
	Test("abca", 0);
	Test("abbc", 0);
	Test("abba", 1);
	Test("bbba", 0);
	Test("accc", 0);
	Test("abcde", 0);
	Test("abcda", 0);
	Test("abcbx", 0);
	Test("abcba", 1);
	Test("bbbba", 0);
	Test("abbbb", 0);
}

int main()
{
	//initfiles();
	Solve();
	return 0;
}
