// http://leetcode.com/2010/09/serializationdeserialization-of-binary.html
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

struct TNode {
    int val;
    TNode* left;
    TNode* right;
    TNode(int x)
        : val(x)
        , left(0)
        , right(0)
    {}
};

void Insert(TNode*& root, int val) {
    if (root == 0) {
        root = new TNode(val);
        return;
    }
    TNode* prev = 0;
    TNode* ptr = root;
    while (ptr) {
        prev = ptr;
        if (val < ptr->val)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    if (val < prev->val)
        prev->left = new TNode(val);
    else
        prev->right = new TNode(val);
}

void DeleteTree(TNode* root) {
	if (root) {
		DeleteTree(root->left);
		DeleteTree(root->right);
		delete root;
	}
}

string ToStr(int x) {
	if (x == 0)
		return "0";
	string res;
	while (x) {
		res.push_back('0' + x % 10);
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

void Serialize(TNode* root, string& str) {
	if (root == 0) {
		str.push_back('#');
		return;
	}
	str += ToStr(root->val) + " ";
	Serialize(root->left, str);
	Serialize(root->right, str);
}

int GetInt(const string& str, int& pos) {
	int res = 0;
	while (isdigit(str[pos]))
		res = res * 10 + (str[pos++] - '0');
	return res;
}

TNode* Deserialize(const string& str, int& pos) {
	if (pos >= str.size())
		return 0;
	if (str[pos] == '#') {
		++pos;
		return 0;
	}
	if (str[pos] == ' ')
		return Deserialize(str, ++pos);
	int x = GetInt(str, pos);
	TNode* res = new TNode(x);
	res->left = Deserialize(str, pos);
	res->right = Deserialize(str, pos);
	return res;
}

void Collect(TNode* root, vector<int>& v) {
	if (root) {
		Collect(root->left, v);
		v.push_back(root->val);
		Collect(root->right, v);
	}
}

void Test() {
	TNode* root = 0;
	const int MAXN = 1000;
	for (int i = 0; i < MAXN; ++i)
		Insert(root, rand() % MAXN);
	string str;
	Serialize(root, str);
	int pos = 0;
	TNode* newRoot = Deserialize(str, pos);

	vector<int> v1, v2;
	Collect(root, v1);
	Collect(newRoot, v2);
	if (v1 == v2 && v1.size() == MAXN)
		cerr << "Ok!\n";
	else
		cerr << "Error!\n";

	DeleteTree(root);
	DeleteTree(newRoot);
}

void Solve() {
	for (int i = 0; i < 10; ++i)
		Test();
	cerr << "Done!\n";
}

int main()
{
	initfiles();
	Solve();
	return 0;
}
