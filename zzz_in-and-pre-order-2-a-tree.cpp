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
    typedef const vector<int> cvi;
	// a - inorder, b - preorder
    TreeNode* dfs(cvi& a, int aSt, int aFn, cvi& b, int bSt, int bFn) {
		if (aSt > aFn)
			return 0;
		if (aSt == aFn)
			return new TreeNode(a[aSt]);
		TreeNode* res = new TreeNode(b[bSt]);
		int aOldSt = aSt;
		while (aSt <= aFn && a[aSt] != b[bSt])
			++aSt;
		res->left = dfs(a, aOldSt, aSt - 1, b, bSt + 1, bSt + (aSt - aOldSt));
		res->right = dfs(a, aSt + 1, aFn, b, bSt + (aSt - aOldSt) + 1, bFn);
		return res;
	}
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return dfs(inorder, 0, (int)inorder.size() - 1, preorder, 0, (int)preorder.size() - 1);
    }
};