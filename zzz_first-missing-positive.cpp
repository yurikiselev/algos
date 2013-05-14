class Solution {
public:
    int Solve(int a[], int n) {
    	for (int i = 0; i < n; ++i) {
			int x = abs(a[i]) - 1;
			if (x >= 0 && x < n)
				a[x] = -abs(a[x]);
		}
		for (int i = 0; i < n; ++i)
			if (a[i] > 0)
				return i + 1;
		return n + 1;
	}
    int firstMissingPositive(int a[], int n) {	
		int cnt = 0;
		for (int i = 0; i < n; ++i)
			if (a[i] > 0)
				a[cnt++] = a[i];
        if (cnt == 0)
            return 1;
		return Solve(a, cnt);
    }
};