/*
      1
   2   3
  4 5   7
     6
	 
	Inorder:   4 2 6 5 _1 3 7
	PostOrder: 4 6 5 2 7 3 _1
	
	Algo:
		1. The root of a tree is in the end of PostOrder traversal;
		2. Find the root in the Inorder traversal;
		3. The position of the root helps split both arrays in to parts: left and right subtrees.
    PS A tree must contain different elements!!!
*/	

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct TNode {
    int val;
    TNode *left;
    TNode *right;
    TNode(int x)
        : val(x)
        , left(0)
        , right(0)
    {}
};

void InOrder(const TNode* root, vector<int>& vert) {
    if (root) {
        InOrder(root->left, vert);
        vert.push_back(root->val);
        InOrder(root->right, vert);
    }
}

void PostOrder(const TNode* root, vector<int>& vert) {
    if (root) {
        PostOrder(root->left, vert);
        PostOrder(root->right, vert);
        vert.push_back(root->val);
    }
}

// a - inorder, b - postorder
TNode* dfs(const vector<int>& a, int aSt, int aFn, const vector<int>& b, int bSt, int bFn) {
    if (aSt > aFn)
        return 0;
    if (aSt == aFn)
        return new TNode(a[aSt]);
    int aOldFn = aFn;
    TNode* res = new TNode(b[bFn]);
    while (aSt <= aFn && a[aFn] != b[bFn])
        --aFn;
    res->left = dfs(a, aSt, aFn - 1, b, bSt, bSt + (aFn - 1 - aSt));
    res->right = dfs(a, aFn + 1, aOldFn, b, bSt + (aFn - aSt), bFn - 1);
    return res;
}

TNode* BuildTree(vector<int>& inorder, vector<int>& postorder) {
    return dfs(inorder, 0, (int)inorder.size() - 1, postorder, 0, (int)postorder.size() - 1);
}

void Insert(TNode*& root, int value) {
    if (root == 0) {
        root = new TNode(value);
    } else {
        TNode* ptr = root;
        TNode* prev = 0;
        while (ptr) {
            prev = ptr;
            if (value < ptr->val)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        TNode* tmp = new TNode(value);
        if (value < prev->val)
            prev->left = tmp;
        else
            prev->right = tmp;
    }
}

void Delete(TNode* root) {
    if (root) {
        Delete(root->left);
        Delete(root->right);
        delete root;
    }
}

void Print(const TNode* root, bool first = true) {
    if (root) {
        Print(root->left, false);
        printf("%d ", root->val);
        Print(root->right, false);
    }
    if (first)
        printf("\n");
}

bool Equal(const TNode* root1, const TNode* root2) {
    vector<int> v1, v2;
    InOrder(root1, v1);
    InOrder(root2, v2);
    return v1 == v2;
}

bool Test() {
    const int MAXN = 10 * 1000;
    for (int t = 0; t < 10; ++t) {
        TNode* root = 0;
        set<int> S; // to avoid repetition!
        for (int i = 0; i < MAXN; ++i) {
            int x = rand();
            while (S.find(x) != S.end())
                x = rand();
            Insert(root, x);
            S.insert(x);
        }
        vector<int> inOrder, postOrder;
        InOrder(root, inOrder);
        PostOrder(root, postOrder);
        TNode* recoveredTree = BuildTree(inOrder, postOrder);
        if (!Equal(root, recoveredTree)) {
            cerr << "Step #" << t << endl;
            Delete(root);
            Delete(recoveredTree);
            return false;
        }
        Delete(root);
        Delete(recoveredTree);
    }
    return true;
}

int main() {
    if (Test())
        cerr << "Ok!\n";
    else
        cerr << "Error!\n";
    cerr << "Done!\n";
    return 0;
}

