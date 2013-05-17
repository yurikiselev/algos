#include <iostream>
#include <algorithm>
using namespace std;

struct TNode {
	int key;
	TNode *left, *right;
	TNode(int x = 0)
		: key(x)
		, left(0)
		, right(0)
	{
	}
};

void Insert(TNode *&root, int key) {
	if (root == 0) {
		root = new TNode(key);
		return;
	}
	TNode *x = root;
	TNode *par = 0;
	while (x) {
		par = x;
		if (x->key >= key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	if (par->key >= key) {
		par->left = new TNode(key);
	} else {
		par->right = new TNode(key);
	}
}

void Wander(TNode *r) {
	if (r) {
		Wander(r->left);
		printf("%d ", r->key);
		Wander(r->right);
	}
}

int main() {
	TNode *root(0);
	for (int i = 0; i < 100; ++i) {
		Insert(root, rand());
	}
	Wander(root);
	return 0;
}