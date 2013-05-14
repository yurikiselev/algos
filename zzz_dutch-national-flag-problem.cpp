// Dutch national flag problem
// http://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/

class Solution {
public:
    void sortColors(int a[], int n) {
		int low = 0;
		int mid = 0;
		int hi = n - 1;
		while (mid <= hi)
			if (a[mid] == 0)
				swap(a[low++], a[mid++]);
			else
				if (a[mid] == 1)
					++mid;
				else
					swap(a[mid], a[hi++]);
    }
};