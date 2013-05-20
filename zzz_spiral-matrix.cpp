class Solution {
public:
    vector<int> res;
	void Out(vector<vector<int> >& a, int n, int m, int k) {
		if (n <= 0 || m <= 0)
			return;
		if (n == 1) {
			for (int i = 0; i < m; ++i)
				res.push_back(a[k][k + i]);
			return;
		}
		if (m == 1) {
			for (int i = 0; i < n; ++i)
				res.push_back(a[k + i][k]);
			return;
		}
		for (int i = 0; i < m - 1; ++i)
			res.push_back(a[k][k + i]);
		for (int i = 0; i < n - 1; ++i)
			res.push_back(a[k + i][k + m - 1]);
		for (int i = 0; i < m - 1; ++i)
			res.push_back(a[k + n - 1][k + m - 1 - i]);
		for (int i = 0; i < n - 1; ++i)
			res.push_back(a[k + n - 1 - i][k]);

		Out(a, n - 2, m - 2, k + 1);
	}
    vector<int> spiralOrder(vector<vector<int> >& a) {
		res.clear();
		int n = a.size();
		if (n == 0)
			return res;
		int m = a[0].size();
		Out(a, n, m, 0);
		return res;
    }
};