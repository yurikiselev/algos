#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <queue>
using namespace std;

void InitFiles() {
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
}

typedef unsigned int Tui;

const size_t MAX_LEN = 500;
const size_t ALPHABET_SIZE = 26;
const Tui PRIME = 3137;
const size_t HASH_TABLE_SIZE = 1000;

Tui Pow[MAX_LEN];
Tui hash[MAX_LEN];

struct THash {
	string s;
	Tui hash;
	THash* next;
	THash(const string& str, Tui h)
		: s(str)
		, hash(h)
		, next(0)
	{
	}
	THash()
		: s("")
		, hash(0)
		, next(0)
	{
	}
};

THash* hashTable[HASH_TABLE_SIZE];

void Insert(Tui h, const string& s) {
	THash* ptr = hashTable[h % HASH_TABLE_SIZE];
	if (ptr == 0) {
		hashTable[h % HASH_TABLE_SIZE] = new THash(s, h);
	} else {
		while (ptr) {
			if (ptr->hash == h && ptr->s == s) {
				return;
			}
			ptr = ptr->next;
		}
		THash* tmp = new THash(s, h);
		tmp->next = hashTable[h % HASH_TABLE_SIZE];
		hashTable[h % HASH_TABLE_SIZE] = tmp;
	}
}

size_t CountAndDelete() {
	size_t res = 0;
	for (size_t i = 0; i < HASH_TABLE_SIZE; ++i) {
		THash* ptr = hashTable[i];
		while (ptr) {
			THash* del = ptr;
			ptr = ptr->next;
			delete del;
			++res;
		}
		hashTable[i] = 0;
	}
	return res;
}

string Generate() {
	string res;
	for (int i = 0; i < MAX_LEN; ++i) {
		res.push_back('a' + rand() % ALPHABET_SIZE);
	}
	return res;
}


size_t CountSet(const string& str) {
	set<string> S;
	for (size_t len = 1; len <= str.size(); ++len) {
		for (size_t pos = 0; pos + len <= str.size(); ++pos) {
			S.insert(str.substr(pos, len));
		}
	}
	return S.size();
}

Tui GetHash(size_t i, size_t j) {
	if (i == 0) {
		return hash[j];
	}
	return hash[j] - Pow[j - i + 1] * hash[i - 1];
}

size_t CountHash(const string& str) {
	Pow[0] = 1;
	for (int i = 1; i < MAX_LEN; ++i) {
		Pow[i] = Pow[i - 1] * PRIME;
	}

	Tui h = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		h = h * PRIME + (str[i] - 'a' + 1);
		hash[i] = h;
	}

	size_t res = 0;
	for (size_t len = 1; len <= str.size(); ++len) {
		for (size_t pos = 0; pos + len <= str.size(); ++pos) {
			Insert(GetHash(pos, pos + len - 1), str.substr(pos, len));
		}
		res += CountAndDelete();
	}
	return res;
}

struct TNode {
	char key;
	TNode* child[ALPHABET_SIZE];
	TNode(char x)
		: key(x)
	{
		memset(child, 0, sizeof(child));
	}
};

void Build(TNode* root, const string& str, size_t pos) {
	if (pos >= str.size()) {
		return;
	}
	if (root->child[str[pos] - 'a'] == 0) {
		root->child[str[pos] - 'a'] = new TNode(str[pos]);
	}
	Build(root->child[str[pos] - 'a'], str, pos + 1);
}

void CountAndDel(TNode* root, size_t& cnt) {
	if (root) {
		++cnt;
		for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
			CountAndDel(root->child[i], cnt);
		}
		delete root;
	}
}

size_t CountTrie(const string& str) {
	TNode* root = new TNode(0);
	for (size_t i = 0; i < str.size(); ++i) {
		Build(root, str, i);
	}
	size_t res = 0;
	CountAndDel(root, res);
	if (res > 0) {
		--res;
	}
	return res;
}

bool Test() {
	string s = Generate();
	size_t cnt1 = CountSet(s);
	size_t cnt2 = CountHash(s);
	size_t cnt3 = CountTrie(s);
	cerr << "\t\t" << cnt1 << ' ' << cnt2 << ' ' << cnt3 << endl;
	return cnt1 == cnt2 && cnt1 == cnt3;
}

int main()
{
	InitFiles();

	for (int i = 0; i < 10; ++i) {
		if (Test()) {
			cout << "Ok!\n";
		} else {
			cout << "Error on step #" << i << endl;
			//return 0;
		}
	}
	cout << "Everything is right!\n";
	return 0;
}