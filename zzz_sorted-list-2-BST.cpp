/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
	ListNode* FindEnd(ListNode* head) {
		while (head->next)
			head = head->next;
		return head;
	}
	ListNode* FindMid(ListNode* head, ListNode* end) {
		ListNode* slow = head;
		ListNode* fast = fast;
		while (fast && fast != end &&
			fast->next && fast->next != end) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
	TreeNode* Construct(ListNode* head, ListNode* end) {
		if (head == 0 || end == 0)
			return 0;
		if (head == end)
			return new TreeNode(head->val);
		ListNode* mid = FindMid(head, end);
		TreeNode* res = new TreeNode(mid->next->val); // mid->next != null - OK
		res->left = Construct(head, mid);
		if (mid != end)
			res->right = Construct(mid->next->next, end);
		return res;			
	}
    TreeNode *sortedListToBST(ListNode *head) {        
		if (head == 0)
			return 0;
		return Construct(head, FindEnd(head));
    }
};