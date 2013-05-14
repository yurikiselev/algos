/*
   8 9 10 1 2 3 4 5 6 7
   l        m         r
			___________ ->sorted part
   
   5 6 7 8 9 10 1 2 3 4
   l       m          r
   _________->sorted part
   
   4 4 4 4 5 6 7 4
   l     m       r
  
*/
  
// no repeated elements
class Solution {
public:
    int search(int a[], int l, int r, int key) {
		if (l > r)
			return -1;
		int m = (l + r) / 2;
		if (a[m] == key)
			return m;
		
		if (a[l] < a[m]) { // left part is sorted
			if (a[l] <= key && key <= a[m])
				return search(a, l, m - 1, key);
			else
				return search(a, m + 1, r, key);
		} else if (a[m] < a[r]) { // right part is sorted
			if (a[m] <= key && key <= a[r])
				return search(a, m + 1, r, key);
			else
				return search(a, l, m - 1, key);
		} else {
			int res = search(a, l, m - 1, key);
			if (res == -1)
				return search(a, m + 1, r, key);
			else
				return res;
		}
		return -1;
	}
    int search(int a[], int n, int key) {
        return search(a, 0, n - 1, key);
    }
};