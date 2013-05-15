class Solution {
    public:
        ListNode* partition(ListNode* head, int x) {
            ListNode* lessBegin = 0;
            ListNode* lessEnd = 0;
            ListNode* grBegin = 0;
            ListNode* grEnd = 0;
            while (head) {
                if (head->val < x) {
                    if (lessBegin == 0)
                        lessBegin = lessEnd = head;
                    else {
                        lessEnd->next = head;
                        lessEnd = lessEnd->next;
                    }
                } else {
                    if (grBegin == 0)
                        grBegin = grEnd = head;
                    else {
                        grEnd->next = head;
                        grEnd = grEnd->next;
                    }
                }
                head = head->next;
            }
            if (lessEnd)
                lessEnd->next = grBegin;
            if (grEnd)
                grEnd->next = 0;
            if (lessBegin)
                return lessBegin;
            return grBegin;
        }
};
