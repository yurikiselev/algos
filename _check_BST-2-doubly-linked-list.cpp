// Binary Search Tree and Double-linked List
// http://codercareer.blogspot.ru/2011/09/interview-question-no-1-binary-search.html

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

void DeleteList(TNode* root) {
    while (root != 0) {
        TNode* nxt = root->right;
        delete root;
        root = nxt;
    }
}

void dfs(TNode* root, TNode*& prev) {
    if (root == 0)
        return;
    if (root->left)
        dfs(root->left, prev);
    root->left = prev;
    if (prev)
        prev->right = root;
    prev = root;
    if (root->right)
        dfs(root->right, prev);
}

TNode* BST2List(TNode* root) {
    TNode* prev = 0;
    dfs(root, prev);
    while (prev && prev->left)
        prev = prev->left;
    return prev;
}

void PrintList(TNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->right;
    }
    printf("\n");
}

void Solve() {
    for (int i = 0; i < 10; ++i) {
        TNode* root = 0;
        GenerateTree(root);
        PrintTree(root);
        printf("\n");
        
        TNode* head = BST2List(root);
        PrintList(head);
        printf("\n");

        DeleteList(head);
    }
}

int main() {
    Solve();
    return 0;
}      
