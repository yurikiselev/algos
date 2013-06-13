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

void PreOrder(const TNode* root, vector<int>& vert) {
    if (root) {
        vert.push_back(root->val);
        PreOrder(root->left, vert);
        PreOrder(root->right, vert);
    }
}

// a - inorder, b - preorder
TNode* dfs(const vector<int>& a, int aSt, int aFn, const vector<int>& b, int bSt, int bFn) {
    if (aSt > aFn)
        return 0;
    if (aSt == aFn)
        return new TNode(a[aSt]);
    TNode* res = new TNode(b[bSt]);
    int aOldSt = aSt;
    while (aSt <= aFn && a[aSt] != b[bSt])
        ++aSt;
    res->left = dfs(a, aOldSt, aSt - 1, b, bSt + 1, bSt + (aSt - aOldSt));
    res->right = dfs(a, aSt + 1, aFn, b, bSt + (aSt - aOldSt) + 1, bFn);
    return res;
}

TNode* BuildTree(vector<int>& preorder, vector<int>& inorder) {
    return dfs(inorder, 0, (int)inorder.size() - 1, preorder, 0, (int)preorder.size() - 1);
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
        vector<int> inOrder, preOrder;
        InOrder(root, inOrder);
        PreOrder(root, preOrder);
        TNode* recoveredTree = BuildTree(preOrder, inOrder);
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

