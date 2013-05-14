/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
		while (root) {
			TreeLinkNode* cur = root;
			while (cur) {
				if (cur->left) {
					if (cur->right)
						cur->left->next = cur->right;
					else {
						TreeLinkNode* nxt = cur->next;
						while (nxt) {
							if (nxt->left) {
								cur->left->next = nxt->left;
								break;
							}
							if (nxt->right) {
								cur->left->next = nxt->right;
								break;
							}
							nxt = nxt->next;
						}
					}
				}
				if (cur->right) {
					TreeLinkNode* nxt = cur->next;
					while (nxt) {
						if (nxt->left) {
							cur->right->next = nxt->left;
							break;
						}
						if (nxt->right) {
							cur->right->next = nxt->right;
							break;
						}
						nxt = nxt->next;
					}
				}
				
				cur = cur->next;
			}
			
			while (root) {
				if (root->left) {
					root = root->left;
					break;
				}
				if (root->right) {
					root = root->right;
					break;
				}
				root = root->next;
			}
		}
    }
};