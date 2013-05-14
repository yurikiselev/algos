#include <iostream>
#include <string>

using namespace std;

typedef unsigned int UI;

class TNode {
public:
	bool terminal;
	TNode *next[26];
	TNode(bool term = false)
		: terminal(term)
	{
		for (int i = 0; i < 26; ++i) {
			next[i] = 0;
		}
	}
};

class TTrie {
private:
	TNode *root;
	bool Insert(TNode *node, const string &s, size_t pos) {
		if (node == 0) {
			return false;
		}
		if (pos >= s.size()) {
			return true;
		}
		if (node->next[s[pos] - 'a'] == 0) {
			node->next[s[pos] - 'a'] = new TNode(pos + 1 == s.size());
		}
		return Insert(node->next[s[pos] - 'a'], s, pos + 1);
	}
	bool Has(TNode *node, const string &s, size_t pos) {
		if (pos == s.size()) {
			return node->terminal;
		}
		if (node->next[s[pos] - 'a']) {
			return Has(node->next[s[pos] - 'a'], s, pos + 1);
		}
		return false;
	}
    void Print(TNode *node, string s) {
        if (node->terminal) {
            printf("%s\n", s.c_str());
        }
        for (int i = 0; i < 26; ++i) {
            if (node->next[i]) {
                Print(node->next[i], s + char('a' + i));
            }
        }
    }
public:
	TTrie() {
		root = new TNode();
	}

	bool Insert(const string &s) {
		return Insert(root, s, 0);
	}

	bool Has(const string &s) {
		return Has(root, s, 0);
	}

    void PrintAll() {
        Print(root, "");
    }
};

TTrie trie;

void Test(const string &s) {
	cout << s << " - ";
	cout << trie.Has(s) << endl;
}

int main() {
	trie.Insert("obama");
	trie.Insert("mama");
	trie.Insert("marat");
	trie.Insert("zzukselz");
	trie.Insert("mamut");
	trie.Insert("mamgo");
	trie.Insert("yuri");
	trie.Insert("yurik");
	trie.Insert("yurikla");
	trie.Insert("zembel");
	Test("ma");
	Test("mama");
	Test("mar");
	Test("marat");
	Test("yuri");
	Test("yurik");
	Test("yurikl");
	Test("yurila");
    printf("==========----------==========\n");
    trie.PrintAll();
	return 0;
}
