#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 10 * 1000;
const int MAX_VAL = 10 * 1000;

class THeap {
private:
    vector<int> v;
private:
    int Par(int x) {
        return x / 2;
    }
    int Left(int x) {
        return x + x;
    }
    int Right(int x) {
        return x + x + 1;
    }
    void MinHeapify(int id) {
        int mi = id;
        int l = Left(id);
        if (l <= Size() && v[l] < v[mi])
            mi = l;
        int r = Right(id);
        if (r <= Size() && v[r] < v[mi])
            mi = r;
        if (mi != id) {
            swap(v[id], v[mi]);
            MinHeapify(mi);
        }

    }
public:
    THeap() {
        v.resize(1);
    }
    int Top() {
        if (Empty())
            throw "Top: empty heap!";
        return v[1];
    }
    int Size() {
        return v.size() - 1;
    }
    bool Empty() {
        return Size() == 0;
    }
    void Pop() {
        if (Empty())
            throw "Pop: empty heap!";
        swap(v[1], v.back());
        v.resize(v.size() - 1);
        if (Size() > 1) // Important check!
            MinHeapify(1);
    }
    void Push(int x) {
        v.push_back(x);
        int id = Size();
        while (Par(id) > 0 && v[id] < v[Par(id)]) {
            swap(v[id], v[Par(id)]);
            id = Par(id);
        }
    }
};

bool Test() {
    int a[MAX_N];
    THeap heap;
    for (int i = 0; i < MAX_N; ++i) {
        int x = rand();
        a[i] = x;
        heap.Push(x);
    }
    sort(a, a + MAX_N);
    for (int i = 0; i < MAX_N; ++i) {
        if (heap.Top() != a[i]) {
            cerr << "bad - " << i << endl;
            return false;
        }
        heap.Pop();
    }
    return heap.Empty();
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
