/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode* root, TreeNode*& n1, TreeNode*& n2, TreeNode*& prev) {
		if (root) {
			dfs(root->left, n1, n2, prev);
			if (prev && prev->val > root->val) {
				// the order matters!!! first root, then prev
				n1 = root;
				if (!n2)
					n2 = prev;
			}
			prev = root;
			dfs(root->right, n1, n2, prev);
		}
	}
    void recoverTree(TreeNode *root) {
		TreeNode* n1 = 0;
		TreeNode* n2 = 0;
		TreeNode* prev = 0;
		dfs(root, n1, n2, prev);
		if (n1 && n2)
			swap(n1->val, n2->val);
    }
};