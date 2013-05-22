#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int MAXN = 1000;

struct TNode {
    int val;
    TNode* next;
    TNode(int x)
        : val(x)
        , next(0)
    {};
};

void AddToBeg(TNode*& head, int val) {
    TNode* tmp = new TNode(val);
    tmp->next = head;
    head = tmp;
}

void AddToEnd(TNode*& head, int val) {
    if (head == 0) {
        head = new TNode(val);
        return;
    }
    TNode* ptr = head;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = new TNode(val);
}

void Delete(TNode* head) {
    if (head == 0)
        return;
    TNode* next = head->next;
    delete head;
    Delete(next);
}

void Collect(TNode* head, vector<int>& v) {
    if (head) {
        v.push_back(head->val);
        Collect(head->next, v);
    }
}

void Reverse(TNode*& head) {
    if (head != 0) {
        TNode* prev = 0;
        TNode* ptr = head;
        while (ptr) {
            TNode* next = ptr->next;
            ptr->next = prev;
            prev = ptr;
            ptr = next;
        }
        head = prev;
    }
}

void Reverse(TNode*& head, int k) {
    if (head == 0 || k <= 1)
        return;
    TNode* prev = 0;
    TNode* ptr = head;
    while (k && ptr) {
        --k;
        TNode* next = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next;
    }
    head->next = ptr;
    head = prev;
}

void Erase(TNode*& head, int key) {
    if (head == 0)
        return;
    if (head->val == key) {
        TNode* tmp = head->next;
        delete head;
        head = tmp;
    } else {
        TNode* prev = head;
        TNode* ptr = head->next;
        while (ptr) {
            if (ptr->val == key) {
                prev->next = ptr->next;
                delete ptr;
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }
}

///del
void Print(const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';
    cout << endl;
}

bool Check(const deque<int>& deq, TNode* head) {
    vector<int> v1, v2;
    for (int i = 0; i < deq.size(); ++i)
        v1.push_back(deq[i]);
    Collect(head, v2);
    return v1 == v2;
}

void Erase(deque<int>& deq, int key) {
    for (size_t i = 0; i < deq.size(); ++i)
        if (key == deq[i]) {
            for (size_t j = i + 1; j < deq.size(); ++j)
                deq[j - 1] = deq[j];
            deq.pop_back();
            return;
        }
}

void Remove(deque<int>& deq, TNode*& head, int key) {
    Erase(head, key);
    Erase(deq, key);
}

bool Test() {
    TNode* head = 0;
    deque<int> deq;

    // Generate
    for (int i = 0; i < MAXN; ++i) {
        int x = rand();
        if (rand() & 1) {
            deq.push_front(x);
            AddToBeg(head, x);
        } else {
            deq.push_back(x);
            AddToEnd(head, x);
        }
    }
    if (!Check(deq, head)) {
        cerr << "\tError in list generation!\n";
        Delete(head);
        return false;
    }

    for (int i = 0; i < MAXN; ++i) {
        if (rand() & 1) { // simple reverse
            reverse(deq.begin(), deq.end());
            Reverse(head);
        } else {
            int k = rand() % deq.size();
            reverse(deq.begin(), deq.begin() + k);
            Reverse(head, k);
        }
    }
    if (!Check(deq, head)) {
        cerr << "\tError in list reversing!\n";
        Delete(head);
        return false;
    }

    for (int i = 0; i < MAXN - 1; ++i) {
        int x = rand() % 10;
        if (x == 0)
            Remove(deq, head, *deq.begin()); // from begin
        if (x == 1)
            Remove(deq, head, *deq.rbegin()); // from end
        if (x == 3)
            Remove(deq, head, rand()); // probably absent value
        if (x > 2)
            Remove(deq, head, deq[rand() % deq.size()]); // same random presented value
    }
    if (!Check(deq, head)) {
        cerr << "\tError in list erasing!\n";
        Delete(head);
        return false;
    }

    Delete(head);
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i) 
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error\n";
    cerr << "Done!\n";
	return 0;
}
