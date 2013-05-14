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

struct TNode {
    int key;
    TNode* left;
    TNode* right;
    TNode* par;
    TNode(int x)
        : key(x)
          , left(0)
          , right(0)
          , par(0)
    {
    }
};

void Insert(TNode*& root, int key) {
    if (root == 0) {
        root = new TNode(key);
    } else {
        TNode* ptr = root;
        TNode* prev = 0;
        while (ptr) {
            prev = ptr;
            if (key < ptr->key) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }
        TNode* tmp = new TNode(key);
        tmp->par = prev;
        if (key < prev->key) {
            prev->left = tmp;
        } else {
            prev->right = tmp;
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

TNode* Find(TNode* root, int key) {
    if (root == 0) {
        return 0;
    }
    if (root->key == key) {
        return root;
    }
    if (key < root->key) {
        return Find(root->left, key);
    }
    return Find(root->right, key);
}

TNode* Next(TNode* root) {
    if (root == 0)
        return 0;
    if (root->right) {
        root = root->right;
        while (root->left)
            root = root->left;
        return root;
    } else {
        TNode* par = root->par;
        while (par && par->right == root) {
            root = par;
            par = par->par;
        }
        return par;
    }
}

TNode* Prev(TNode* root) {
    if (root == 0)
        return 0;
    if (root->left) {
        root = root->left;
        while (root->right)
            root = root->right;
        return root;
    } else {
        TNode* par = root->par;
        while (par && par->left == root) {
            root = par;
            par = par->par;
        }
        return par;
    }
}

//          10
//     7        18
//   6   9    15    20
//  5 8     14  16
//         13    17

void Solve() {
    TNode* root = 0;
    Insert(root, 10);
    Insert(root, 7);
    Insert(root, 9);
    Insert(root, 6);
    Insert(root, 5);
    Insert(root, 8);
    Insert(root, 18);
    Insert(root, 20);
    Insert(root, 15);
    Insert(root, 16);
    Insert(root, 17);
    Insert(root, 14);
    Insert(root, 13);
    Print(root);

    {
        if (Next(Find(root, 0)) != NULL) {
            cerr << "Next: error! 0\n";
        }
        if (Next(Find(root, 5))->key != 6) {
            cerr << "Next: error! 5\n";
        }
        if (Next(Find(root, 6))->key != 7) {
            cerr << "Next: error! 6\n";
        }
        if (Next(Find(root, 9))->key != 10) {
            cerr << "Next: error! 9\n";
        }
        if (Next(Find(root, 20)) != NULL) {
            cerr << "Next: error! 20\n";
        }
        if (Next(Find(root, 13))->key != 14) {
            cerr << "Next: error! 13\n";
        }
        if (Next(Find(root, 17))->key != 18) {
            cerr << "Next: error! 17\n";
        }
    }
    {
        if (Prev(Find(root, 0)) != NULL) {
            cerr << "Prev: error! 0\n";
        }
        if (Prev(Find(root, 5)) != NULL) {
            cerr << "Prev: error! 5\n";
        }
        if (Prev(Find(root, 6))->key != 5) {
            cerr << "Prev: error! 6\n";
        }
        if (Prev(Find(root, 8))->key != 7) {
            cerr << "Prev: error! 8\n";
        }
        if (Prev(Find(root, 18))->key != 17) {
            cerr << "Prev: error! 18\n";
        }
        if (Prev(Find(root, 13))->key != 10) {
            cerr << "Prev: error! 13\n";
        }
    }
    cerr << "Done!\n";
}

int main()
{
    initfiles();
    Solve();
    return 0;
}

