/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *swapPairs(ListNode* head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == 0)
            return 0;
        if (head->next == 0)
            return head;

        ListNode* prev = 0;
        ListNode* ptr = head;
        ListNode* nxt = head->next;
        ListNode* res = 0;
        while (nxt) {
            if (prev)
                prev->next = nxt;
            else
                res = nxt;
            ListNode* tmp = nxt->next;
            nxt->next = ptr;
            ptr->next = tmp;
            
            prev = ptr;
            if (prev)
                ptr = prev->next;
            else
                break;
            if (ptr)
                nxt = ptr->next;
            else
                break;
        }
        return res;
    }
};