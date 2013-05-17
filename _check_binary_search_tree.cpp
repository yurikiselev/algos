#include <iostream>
#include <vector>
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

void InorderWander(TNode *root, vector<int>& res) {
	if (root) {
		InorderWander(root->left, res);
        res.push_back(root->key);
		InorderWander(root->right, res);
	}
}

void Delete(TNode* root) {
    if (root) {
        Delete(root->left);
        Delete(root->right);
        delete root;
    }
}

bool Test() {
    const int MAXN = 100 * 1000;
    TNode* root = 0;
    vector<int> etalon;
    for (int i = 0; i < MAXN; ++i) {
        int x = rand();
        Insert(root, x);
        etalon.push_back(x);
    }
    sort(etalon.begin(), etalon.end());
    vector<int> res;
    InorderWander(root, res);
    Delete(root);
    return res == etalon;
}

int main() {
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
