#include "iostream"
#include "string"
#include "stack"
#include "exception"
#include "algorithm"

using namespace std;

struct TNode {
    char value;
    TNode* next;
    TNode(char c)
        : value(c)
        , next(0)
    {}
};

void AddToBeg(TNode*& head, char value) {
    TNode* tmp = new TNode(value);
    tmp->next = head;
    head = tmp;
}

bool IsPal(TNode* head) {
	TNode* slow = head;
	TNode* fast = head;
	stack<char> st;
	while (fast != 0 && fast->next != 0) {
		st.push(slow->value);
		slow = slow->next;
		fast = fast->next->next;
	}
	if (fast != 0)
		slow = slow->next;
	while (slow != 0) {
		if (slow->value != st.top())
			return false;
		slow = slow->next;
		st.pop();
	}
	return true;
}

bool IsPal(const char* s) {
	const char* slow = s;
	const char* fast = s;
	stack<char> st;
	while (*fast != '\0' && *(fast + 1) != '\0') {
		st.push(*slow);
		slow += 1;
		fast += 2;
	}
	if (*fast != '\0')
		++slow;
	while (*slow != 0) {
		if (*slow != st.top())
			return false;
		++slow;
		st.pop();
	}
	return true;
}

TNode* GetList(const string& s) {
    TNode* head = 0;
    for (int i = (int) s.size() - 1; i >= 0; --i)
        AddToBeg(head, s[i]);
    return head;
}

void Delete(TNode* head) {
    if (head) {
        Delete(head->next);
        delete head;
    }
}

string Print(TNode* head) {
    string res;
    while (head) {
        res.push_back(head->value);
        head = head->next;
    }
    return res;
}

bool Test(const string& s) {
    TNode* head = GetList(s);
    if (s != Print(head))
        throw "Error in list converting!\n";
    if (IsPal(s.c_str()) != IsPal(head)) {
        cerr << s << ' ' << IsPal(s.c_str()) << ' ' << IsPal(head) << endl;
        return false;
    }
    Delete(head);
    return true;
}

bool SmallTest() {
    for (int t = 0; t < 1000; ++t) {
        string s;
        int len = rand() % 6;
        for (int i = 0; i < len; ++i)
            s.push_back('a' + rand() % 3);
        if (!Test(s))
            return false;
    }
    return true;
}

bool BigTest() {
    for (int t = 0; t < 100; ++t) {
        string s;
        int len = rand() % 10000 + 1;
        for (int i = 0; i < len; ++i)
            s.push_back('a' + rand() % 26);
        string revS = s;
        reverse(revS.begin(), revS.end());
        if (rand() % 2 == 0)
            s.resize(s.size() - 1);
        s = s + revS;
        if (rand() % 2 == 0)
            s[rand() % s.size()] = 'a' + (rand() % 26);
        if (!Test(s))
            return false;
    }
    return true;
}

int main() {
    if (SmallTest())
        cerr << "SmallTest: ok!\n";
    else
        cerr << "SmallTest: error!\n";
    if (BigTest())
        cerr << "BigTest: ok!\n";
    else
        cerr << "BigTest: error!\n";
    return 0;
}

