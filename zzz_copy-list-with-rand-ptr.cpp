#include <iostream>

struct TNode {
	int key;
	TNode* next;
	TNode* rand;
	TNode(int x)
		: key(x)
		, next(0)
		, rand(0)
	{
	}
};

TNode* Init() {
	TNode* first = new TNode(10);
	TNode* second = new TNode(20);
	TNode* third = new TNode(30);
	TNode* fourth = new TNode(40);

	first->next = second;
	first->rand = fourth;

	second->next = third;
	second->rand = second;

	third->next = fourth;
	third->rand = second;

	fourth->next = 0;
	fourth->rand = first;

	return first;
}

void Print(TNode* root) {
	if (root) {
		printf("value = %d, ", root->key);
		if (root->next) {
			printf("next = %d, ", root->next->key);
		} else {
			printf("next = NULL, ");
		}
		if (root->rand) {
			printf("rand = %d\n", root->rand->key);
		} else {
			printf("rand = NULL\n");
		}
		Print(root->next);
	}
}

TNode* Copy(TNode*& root) {
	if (root == 0) {
		return 0;
	}

	TNode* ptr = root;
	while (ptr) {
		TNode* next = ptr->next;
		TNode* tmp = new TNode(ptr->key);
		ptr->next = tmp;
		tmp->next = next;
		ptr = ptr->next->next;
	}

	ptr = root;
	while (ptr && ptr->next) {
		ptr->next->rand = ptr->rand->next;
		ptr = ptr->next->next;
	}

	TNode* clone = root->next;
	TNode* orig = root;
	TNode* res = clone;
	while (clone->next) {
		orig->next = orig->next->next;
		clone->next = clone->next->next;
		orig = orig->next;
		clone = clone->next;
	}
	orig->next = 0;

	return res;
}

int main()
{
	TNode* root = Init();
	printf("Origin list:\n");
	Print(root);
	printf("\n");

	TNode* copy = Copy(root);
	Print(root);
	printf("\n");
	Print(copy);
	return 0;
}