#include <iostream>
#include <set>
#include <vector>

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
	UI rHash = hash & (MAXN - 1); // stands for "reduce hash"
    TNode *tmp = new TNode(hash, value);
    tmp->next = hashTable[rHash];
    hashTable[rHash] = tmp;
}

bool Has(UI hash, int value) {
    UI rHash = hash & (MAXN - 1);
    TNode* ptr = hashTable[rHash];
    while (ptr) {
        if (ptr->value == value)
            return true;
        ptr = ptr->next;
    }
    return false;
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

void ClearAndReset() {
    for (int i = 0; i < MAXN; ++i) {
        TNode* ptr = hashTable[i];
        while (ptr) {
            TNode* next = ptr->next;
            delete ptr;
            ptr = next;
        }
        hashTable[i] = 0;
    }
}

bool Test() {
    ClearAndReset();
    set<int> S;
    vector<int> v;
    cerr << "has: ";
    for (int i = 0; i < 10 * 1000; ++i) {
        int op = rand() % 3;
        if (S.size() == 0)
            op = 1;
        if (op > 0) { // insert
            int val = rand();
            S.insert(val);
            Add(val, val);
            v.push_back(val);
        } else { // delete
            int x = v[rand() % v.size()];
            S.erase(x);
            Remove(x, x);
        }
        if (!v.empty()) {
            for (int j = 0; j < 5; ++j) {
                int id = rand() % v.size();
                bool has1 = S.find(v[id]) != S.end();
                bool has2 = Has(v[id], v[id]);
                if (i % 1000 == 0)
                    cerr << has1;
                if (has1 != has2)
                    return false;
            }
        }
    }
    cerr << "\n";
    return true;
}

int main() {
    for (int i = 0; i < 10; ++i)
        if (Test())
            cerr << "Ok!\n";
        else
            cerr << "Error!\n";
    cerr << "Done!\n";
	return 0;
}
