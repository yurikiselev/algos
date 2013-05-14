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
#include <limits>
using namespace std;

void initfiles() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
}

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
    bool LenIsEnough(ListNode* head, int k) {
		while (head && k > 1) {
			head = head->next;
			--k;
		}
		return head != 0;
	}
	
	ListNode* Reverse(ListNode* head, int k) {
		if (!LenIsEnough(head, k))
			return head;
		int K = k;
		ListNode* prev = 0;
		ListNode* ptr = head;
		while (k) {
			ListNode* tmp = ptr->next;
			ptr->next = prev;
			prev = ptr;
			ptr = tmp;
			--k;
		}
		head->next = Reverse(ptr, K);
		return prev;
	}
	
    ListNode *reverseKGroup(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return Reverse(head, k);
    }

	void Print(ListNode* root) {
		while (root) {
			printf("%d ", root->val);
			root = root->next;
		}
		printf("\n");
	}

void Solve() {
	ListNode* root = new ListNode(1);
	root->next = new ListNode(2);
	Print(Reverse(root, 2));
}

int main()
{
	initfiles();
	Solve();
	return 0;
}
