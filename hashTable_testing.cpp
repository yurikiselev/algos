#include <iostream>

using namespace std;

typedef unsigned int UI;

const int MAXN = 1 << 20;

class TNode {
public:
	UI hash;
	int value;
	TNode *next;
	TNode(UI Hash, int Value)
		: hash(Hash)
		, value(Value)
		, next(0)
	{
	}
};

TNode *hashTable[MAXN];

void Add(UI hash, int value) {
	UI rHash = hash & (MAXN - 1);
	if (hashTable[rHash] == 0) {
		hashTable[rHash] = new TNode(hash, value);
	} else {
		TNode *tmp = new TNode(hash, value);
		tmp->next = hashTable[rHash];
		hashTable[rHash] = tmp;
	}
}

bool Remove(UI hash, int value) {
	UI rHash = hash & (MAXN - 1);
	if (hashTable[rHash] == 0) {
		return false;
	}

	TNode *ptr = hashTable[rHash];
	if (ptr->hash == hash && ptr->value == value) {
		TNode *tmp = ptr->next;
		delete ptr;
		hashTable[rHash] = tmp;
		return true;
	}

	TNode *next = ptr->next;
	while (next) {
		if (next->hash == hash && next->value == value) {
			ptr->next = next->next;
			delete next;
			return true;
		}
		ptr = next;
		next = next->next;
	}

	return false;
}

void Testing() {
	Add(10, 50);
	Add(10, 500);
	Add(10, 5000);
	Add(16, 1);
	Add(31, 100500);
	Add(31, 100501);
	Add(32, 100500);
	Add(32, 100501);

	if (Remove(10, 2)) {
		cerr << "Removed (" << 10 << "; " << 2 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(15, 1)) {
		cerr << "Removed (" << 15 << "; " << 1 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(16, 2)) {
		cerr << "Removed (" << 16 << "; " << 2 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(17, 1)) {
		cerr << "Removed (" << 17 << "; " << 1 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(30, 18)) {
		cerr << "Removed (" << 30 << "; " << 18 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(32, 18)) {
		cerr << "Removed (" << 32 << "; " << 18 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(31, 18)) {
		cerr << "Removed (" << 31 << "; " << 18 << ")... WTF???\n";
	} else {
		cerr << "ok\n";
	}
	if (Remove(10, 500)) {
		cerr << "Removed (" << 10 << "; " << 500 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(10, 50)) {
		cerr << "Removed (" << 10 << "; " << 50 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(10, 5000)) {
		cerr << "Removed (" << 10 << "; " << 5000 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(16, 1)) {
		cerr << "Removed (" << 16 << "; " << 1 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(31, 100500)) {
		cerr << "Removed (" << 31 << "; " << 100500 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(31, 100501)) {
		cerr << "Removed (" << 31 << "; " << 100501 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(32, 100500)) {
		cerr << "Removed (" << 32 << "; " << 100501 << ")\n";
	} else {
		cerr << "error\n";
	}
	if (Remove(32, 100501)) {
		cerr << "Removed (" << 32 << "; " << 100500 << ")\n";
	} else {
		cerr << "error\n";
	}
}

int main() {
	Testing();
	return 0;
}