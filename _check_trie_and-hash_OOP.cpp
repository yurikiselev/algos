#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

typedef unsigned long long ULL;

const int MAX_LEN = 200;
const int ALPHABET_SIZE = 10;

class Trie {
private:
	struct TNode {
		char c;
		bool isTerm;
		TNode* ch[ALPHABET_SIZE];
		TNode(char sym, bool term)
			: c(sym)
			, isTerm(term)
		{
			memset(ch, 0, sizeof(ch));
		}
	};
	TNode* root;
	
private:
	bool Has(TNode* root, const string& s, int pos) {
		if (root == 0)
			return false;
		if (pos == s.size())
			return root->isTerm;
		TNode* next = root->ch[s[pos] - 'a'];
		if (next == 0)
			return false;
		return Has(next, s, pos + 1);
	}
	void Insert(TNode* root, const string& s, int pos) {
		if (pos == s.size())
			return;
		if (root->ch[s[pos] - 'a'] == 0)
			root->ch[s[pos] - 'a'] = new TNode(s[pos], pos + 1 == s.size());
		Insert(root->ch[s[pos] - 'a'], s, pos + 1);
	}
	void Delete(TNode* root) {
		if (root == 0)
			return;
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if (root->ch[i] != 0)
				Delete(root->ch[i]);
		delete root;
	}
	int WordsCount(TNode* root) {
		if (root == 0)
			return 0;
		int res = (root->isTerm ? 1 : 0);
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if (root->ch[i])
				res += WordsCount(root->ch[i]);
		return res;
	}
public:
	Trie() {
		root = new TNode('\0', false);
	}
	bool Has(const string& s) {
		return Has(root, s, 0);
	}
	void Insert(const string& s) {
		Insert(root, s, 0);
	}
	int WordsCount() {
		return WordsCount(root);
	}
	~Trie() {
		Delete(root);
	}
};

class THashHelper {
private:
	static const ULL PRIME = 3137LL;

	ULL pow[MAX_LEN];
	ULL hash[MAX_LEN];
public:
	THashHelper(const string& s) {
		pow[0] = 1;
		for (int i = 1; i < s.size(); ++i)
			pow[i] = pow[i - 1] * PRIME;
		ULL h = 0;
		for (int i = 0; i < s.size(); ++i) {
			h = h * PRIME + (s[i] - 'a' + 1);
			hash[i] = h;
		}
	}
	ULL GetHash(int i, int j) {
		if (i == 0)
			return hash[j];
		return hash[j] - hash[i - 1] * pow[j - i + 1];
	}
};

class THashTable {
private:
	struct TNode {
		ULL key;
		TNode* next;
		TNode(ULL x)
			: key(x)
			, next(0)
		{}
	};
	static const int HASH_TABLE_SIZE = 1 << 15;
	TNode* hashTable[HASH_TABLE_SIZE];
public:
	THashTable() { // don't forget!
		memset(hashTable, 0, sizeof(hashTable));
	}
	void Insert(ULL key, const string& s) {
		int hash = key % HASH_TABLE_SIZE;
		TNode* ptr = hashTable[hash];
		while (ptr) {
			if (ptr->key == key)
				return;
			ptr = ptr->next;
		}
		TNode* tmp = new TNode(key);
		tmp->next = hashTable[hash];
		hashTable[hash] = tmp;
	}
	int WordsCount() {
		int res = 0;
		for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
			TNode* ptr = hashTable[i];
			while (ptr) {
				++res;
				ptr = ptr->next;
			}
		}
		return res;
	}
	~THashTable() {
		for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
			TNode* ptr = hashTable[i];
			while (ptr) {
				TNode* next = ptr->next;
				delete ptr;
				ptr = next;
			}
		}
	}
};

string Generate() {
	string res;
	for (int i = 0; i < MAX_LEN; ++i)
		res.push_back('a' + rand() % ALPHABET_SIZE);
	return res;
}

int CountSet(const string& s) {
	int res = 0;
	for (int len = 1; len <= MAX_LEN; ++len) {
		set<string> S;
		for (int pos = 0; pos + len <= MAX_LEN; ++pos)
			S.insert(s.substr(pos, len));
		res += (int)S.size();
	}
	return res;
}

int CountTrie(const string& s) {
	Trie trie;
	for (int len = 1; len <= MAX_LEN; ++len) {
		for (int pos = 0; pos + len <= MAX_LEN; ++pos)
			trie.Insert(s.substr(pos, len));
	}
	return trie.WordsCount();
}

int CountHash(const string& s) {
	THashHelper hashHelper(s);
	int res = 0;
	for (int len = 1; len <= MAX_LEN; ++len) {
		THashTable hashTable;
		for (int pos = 0; pos + len <= MAX_LEN; ++pos)
			hashTable.Insert(hashHelper.GetHash(pos, pos + len - 1), s.substr(pos, len));
		res += hashTable.WordsCount();
	}
	return res;
}

bool Test() {
	string s = Generate();
	int cnt1 = CountSet(s);
	int cnt2 = CountTrie(s);
	int cnt3 = CountHash(s);
	cerr << "\t" << cnt1 << ' ' << cnt2 << ' ' << cnt3 << endl;
	return cnt1 == cnt2 && cnt2 == cnt3;
}

int main() {
	for (int i = 0; i < 10; ++i)
		if (!Test())
			cerr << "Error!\n";
		else
			cerr << "Ok!\n";
	cerr << "Done!\n";
	return 0;
}