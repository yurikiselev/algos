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
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

bool Match(char* temp, char* str) {
	if (*temp == '\0' && *str == '\0')
		return true;
	if (*temp == '*' && *(temp + 1) != '\0' && *str == '\0')
		return false;
	if (*temp == '?' || *temp == *str)
		return Match(temp + 1, str + 1);
	if (*temp == '*')
		return Match(temp + 1, str) || Match(temp, str + 1);
	return false;
}

void test(char *first, char *second)
{
	Match(first, second) ? puts("Yes"): puts("No");
}

void Solve() {
	test("g*ks", "geeks"); // Yes
    test("ge?ks*", "geeksforgeeks"); // Yes
    test("g*k", "gee");  // No because 'k' is not in second
    test("*pqrs", "pqrst"); // No because 't' is not in first
    test("abc*bcd", "abcdhghgbcd"); // Yes
    test("abc*c?d", "abcd"); // No because second must have 2 instances of 'c'
    test("*c*d", "abcd"); // Yes
    test("*?c*d", "abcd"); // Yes
}

int main()
{
	initfiles();
	Solve();
	return 0;
}