// http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <functional>
#include <queue>
#include <stack>
#include <iterator>

using namespace std;

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

void PrintTree(TNode* root) {
    if (root) {
        PrintTree(root->left);
        printf("%d ", root->val);
        PrintTree(root->right);
    }
}

void GenerateTree(TNode*& root) {
    for (int i = 0; i < 20; ++i)
        Insert(root, rand() % 1000);
}

void DeleteTree(TNode* root) {
    if (root != 0) {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
}

void dfs(TNode* root, vector<int>& v) {
    if (root) {
        dfs(root->left, v);
        v.push_back(root->val);
        dfs(root->right, v);
    }
}

void InorderStack(TNode* root, vector<int>& v) {
    stack<TNode*> st;
    while (true) {
        while (root) {
            st.push(root);
            root = root->left;
        }
        if (st.empty())
            break;
        root = st.top();
        st.pop();
        v.push_back(root->val);
        root = root->right;
    }
}

void MorrisTraversal(TNode* root, vector<int>& v) {
    while (root) {
        if (!root->left) {
            v.push_back(root->val);
            root = root->right;
        } else {
            TNode* next = root->left;
            while (next->right && next->right != root)
                next = next->right;
            if (next->right == root) {
                v.push_back(root->val); // don't forget!!!
                next->right = 0;
                root = root->right;
            } else {
                next->right = root;
                root = root->left;
            }
        }
    }
}

void Solve() {
    TNode* root = 0;
    for (int i = 0; i < 30; ++i) {
        vector<int> v1, v2, v3;
        GenerateTree(root);
        PrintTree(root);
        printf("\n");

        dfs(root, v1);
        InorderStack(root, v2);
        MorrisTraversal(root, v3);
        if (v1 != v2 || v2 != v3)
            cout << "Error!\n";

        DeleteTree(root);
        root = 0;
    }
    cerr << "Done!\n";
}

int main() {
    Solve();
    return 0;
}      

