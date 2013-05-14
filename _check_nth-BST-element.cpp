#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TNode {
	int key;
	int size;
	TNode* left;
	TNode* right;
	TNode(int x = 0, int sz = 0)
		: key(x)
		, size(sz)
		, left(0)
		, right(0)
	{
	}
};

void Insert(TNode*& root, int key) {
	if (root == 0) {
		root = new TNode(key, 1);
	} else {
		TNode* ptr = root;
		TNode* prev = 0;
		while (ptr) {
			ptr->size++;
			prev = ptr;
			if (key < ptr->key) {
				ptr = ptr->left;
			} else {
				ptr = ptr->right;
			}
		}
		if (key < prev->key) {
			prev->left = new TNode(key, 1);
		} else {
			prev->right = new TNode(key, 1);
		}
	}
}

void Print(TNode* root) {
	if (root) {
		Print(root->left);
		printf("%d ", root->key);
		Print(root->right);
	}
}

///////////////////////////////////////////////////start
TNode* FindRec(TNode* root, int k) {
	if (root == 0) {
		return 0;
	}
	if (k > root->size) {
		return 0;
	}
	if (root->left && k <= root->left->size) {
		return FindRec(root->left, k);
	}
	int left = (root->left ? root->left->size : 0) + 1;
	if (left == k) {
		return root;
	}
	return FindRec(root->right, k - left);
}

TNode* Find(TNode* root, int k) {
	k++;
	return FindRec(root, k);
}
///////////////////////////////////////////////////end

///////////////////////////////////////////////////start
TNode* FindK(TNode* root, int k, int& cnt) {
	if (!root)
		return 0;

	TNode* tmp = FindK(root->left, k, cnt);
	if (tmp)
		return tmp;

	++cnt;
	if (cnt == k)
		return root;

	return FindK(root->right, k, cnt);
}

TNode* FindK(TNode* root, int k) {
	++k;
	int cnt = 0;
	return FindK(root, k, cnt);
}
///////////////////////////////////////////////////end

int main()
{
	vector<int> v;
	TNode* root = 0;
	for (int i = 0; i < 10000; ++i) {
		int x = rand();
		v.push_back(x);
		Insert(root, x);
	}

	Print(root);
	printf("\n");

	sort(v.begin(), v.end());
	for (int i = 0; i < 10 * 1000; ++i) {
		int id = rand() % v.size();
		if (v[id] != Find(root, id)->key) {
			cerr << "Error! Step #" << i << endl;
			return 0;
		}
		if (v[id] != FindK(root, id)->key) {
			cerr << "Error! Step #" << i << endl;
			return 0;
		}
	}
	cerr << "Everything is OK!\n";

	return 0;
}
