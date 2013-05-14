#include <iostream>

using namespace std;

typedef unsigned int UI;

const int MAXN = 1 << 20;

class TNode {
public:
	int value;
	UI hash;
	TNode *next;
	TNode(int Value = 0, UI Hash = 0) 
		: value(Value)
		, hash(Hash)
		, next(0)
	{
	}
};

TNode *hashTable[MAXN];

void Add(UI hash, int value) {
	UI rHash = hash & (MAXN - 1);
	if (hashTable[rHash] == 0) {
		hashTable[rHash] = new TNode(value, hash);
		return;
	} else {
		TNode *tmp = new TNode(value, hash);
		tmp->next = hashTable[rHash];
		hashTable[rHash] = tmp;
	}
}

bool Remove(UI hash, int value) {
	TNode *ptr = hashTable[hash & (MAXN - 1)];
	if (!ptr) {
		return false;
	}
	if (ptr->hash == hash && ptr->value == value) {
		TNode *tmp = ptr->next;
		delete ptr;
		hashTable[hash & (MAXN - 1)] = tmp;
		return true;
	}
	
	TNode *next = ptr->next;
	while (next) {
		if (next->hash == hash && next->value == value) {
			TNode *tmp = next->next;
			delete next;
			ptr->next = tmp;
			next = tmp;
			return true;
		}
		ptr = next;
		next = next->next;
	}
	return false;
}

int main() {
	return 0;
}