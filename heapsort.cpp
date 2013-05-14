#include <iostream>
#include <vector>

using namespace std;

class THeap {
private:
	vector<int> v;
	// elements indexing from 1 to Size(), Size() + 1 = v.size()
	int Parent(int x) {
		return x >> 1;
	}
	int Left(int x) {
		return x << 1;
	}
	int Right(int x) {
		return (x << 1) | 1;
	}
	void MaxHeapify(int id) {
		int l = Left(id);
		int r = Right(id);
		int largest = id;
		if (l <= Size() && v[l] > v[id]) {
			largest = l;
		}
		
		if (r <= Size() && v[r] > v[largest]) {
			largest = r;
		}
		if (largest != id) {
			swap(v[id], v[largest]);
			MaxHeapify(largest);
		}
	}
public:
	THeap() {
		v.resize(1);
	}
	int Size() {
        cerr << "size ------- " << v.size() - 1 << endl;
		return v.size() - 1;
	}
	void Push(int value) {
		v.push_back(value);
		int id = Size();
		while (id > 1 && v[Parent(id)] < v[id]) {
			swap(v[Parent(id)], v[id]);
			id = Parent(id);
		}
	}
	int Top() {
		return v[1]; // check Size()!
	}
	void Pop() {
		v[1] = v.back(); // check Size()!
		v.resize(v.size() - 1);
		if (Size() != 0) { // important, otherwise it's crash!
			MaxHeapify(1);
		}
	}
};

int main() {
	int n;
	scanf("%d", &n);
	THeap heap;
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		heap.Push(x);
	}

	while (heap.Size() > 0) {
		printf("%d\n", heap.Top());
		heap.Pop();
	}
	return 0;
}
