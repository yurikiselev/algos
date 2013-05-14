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
*/	

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
	// a - inorder, b - postorder
	TreeNode* dfs(cvi& a, int aSt, int aFn, cvi& b, int bSt, int bFn) {
		if (aSt > aFn)
			return 0;
		if (aSt == aFn)
			return new TreeNode(a[aSt]);
		int aOldFn = aFn;
		TreeNode* res = new TreeNode(b[bFn]);
		while (aSt <= aFn && a[aFn] != b[bFn])
			--aFn;
		res->left = dfs(a, aSt, aFn - 1, b, bSt, bSt + (aFn - 1 - aSt));
		res->right = dfs(a, aFn + 1, aOldFn, b, bSt + (aFn - aSt), bFn - 1);
		return res;
	}
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		return dfs(inorder, 0, (int)inorder.size() - 1, postorder, 0, (int)postorder.size() - 1);
    }
};