#include <iostream>

struct TNode {
    int val;
    TNode* next;
    TNode(int x)
        : val(x)
        , next(0)
    {
    }
};

TNode* AddToBeg(TNode* root, int val) {
    TNode* tmp = new TNode(val);
    tmp->next = root;
    return tmp;
}

TNode* AddToEnd(TNode* root, int val) {
    if (root == 0) {
        return new TNode(val);
    }
    TNode* ptr = root;
    while (ptr->next) {
        ptr = ptr->next;
    }
    TNode* tmp = new TNode(val);
    ptr->next = tmp;
    return root;
}

void Print(TNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

TNode* Reverse(TNode* head) {
    if (head == 0) {
        return head;
    }
    TNode* prev = 0;
    TNode* next = head;
    while (next) {
        TNode* tmp = next->next;
        next->next = prev;
        prev = next;
        next = tmp;
    }
    return prev;
}

TNode* Reverse(TNode* head, int k) {
    if (head == 0 || k <= 1) {
        return head;
    }

    TNode* first = head;
    TNode* ptr = first->next;
    while (ptr && k > 1) { // don't forget the first condition!!!
        --k;
        TNode* next = ptr->next;
        ptr->next = first;
        first = ptr;
        ptr = next;
    }
    head->next = ptr;
    return first;
}

TNode* Erase(TNode* head, int val) {
    if (head == 0) {
        return head;
    }

    if (head->val == val) {
        TNode* tmp = head->next;
        delete head;
        return tmp;
    }

    TNode* prev = head;
    TNode* ptr = head->next;
    while (ptr) {
        if (ptr->val == val) {
            prev->next = ptr->next;
            delete ptr;
            return head;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

int main() {
    TNode* root = 0;
    for (int i = 0; i < 10; ++i) {
        if (i % 2) {
            root = AddToBeg(root, i);
        } else {
            root = AddToEnd(root, i);
        }
    }
    Print(root);
    root = Reverse(root);
    Print(root);
    root = Reverse(root, 5);
    Print(root);
    root = Reverse(root, 100500);
    Print(root);
    root = Erase(root, 9);
    root = Erase(root, 1);
    root = Erase(root, 0);
    Print(root);
    return 0;
}
