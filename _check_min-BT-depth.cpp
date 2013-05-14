#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <stack>
#include <functional>
#include <queue>
#include <iterator>
#include <cmath>

using namespace std;

 struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };

class Solution {
    public:
        static int minDepthRec(TreeNode* root, int h) {
            if (root == 0)
                return 0;
            int h1 = minDepthRec(root->left, h);
            int h2 = minDepthRec(root->right, h);
            if (root->left && root->right)
                return min(h1, h2) + 1;
            if (root->left)
                return h1 + 1;
            return h2 + 1;
        }
        static int minDepthRec(TreeNode *root) {
            return minDepthRec(root, 0);
        }
        static int minDepthQueue(TreeNode* root) {
            if (root == 0)
                return 0;
            queue< pair<TreeNode*, int> > q; // queue, not stack!!!
            q.push(make_pair(root, 1));
            while (!q.empty()) {
                root = q.front().first;
                int depth = q.front().second;
                q.pop();
                if (root->left == 0 && root->right == 0)
                    return depth;
                if (root->left)
                    q.push(make_pair(root->left, depth + 1));
                if (root->right)
                    q.push(make_pair(root->right, depth + 1));
            }
        }
};

void Generate(TreeNode*& root) {
    root = new TreeNode(rand() % 1000);
    for (int i = 0; i < 5; ++i) {
        int x = rand() % 1000;
        TreeNode* ptr = root;
        while (1) {
            if (rand() & 1) { // left
                if (ptr->left)
                    ptr = ptr->left;
                else {
                    ptr->left = new TreeNode(x);
                    break;
                }
            } else { // right
                if (ptr->right)
                    ptr = ptr->right;
                else {
                    ptr->right = new TreeNode(x);
                    break;
                }
            }
        }
    }
}

void Delete(TreeNode* root) {
    if (root == 0)
        return;
    Delete(root->left);
    Delete(root->right);
    delete(root);
}

int main()
{
    for (int i = 0; i < 10 * 1000 ; ++i) {
        TreeNode* root = 0;
        Generate(root);
        if (Solution::minDepthRec(root) != Solution::minDepthQueue(root))
            cerr << i << ' ';
        Delete(root);
    }
    cerr << "Done!\n";
    return 0;
}      
