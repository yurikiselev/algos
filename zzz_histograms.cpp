class Solution {
public:
    int largestRectangleArea(vector<int>& a) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
   
    	int n = a.size();
		if (n == 0)
			return 0;
		
		vector<int> L(n), R(n);
		{
			stack<int> st;
			for (int i = 0; i < n; ++i) {
				while (!st.empty() && a[st.top()] >= a[i])
					st.pop();
				L[i] = st.empty() ? -1 : st.top();
				st.push(i);
			}
		}
		{
			stack<int> st;
			for (int i = n - 1; i >= 0; --i) {
				while (!st.empty() && a[st.top()] >= a[i])
					st.pop();
				R[i] = st.empty() ? n : st.top();
				st.push(i);
			}
		}
		int res = 0;
		for (int i = 0; i < n; ++i)
			res = max(res, a[i] * (R[i] - L[i] - 1));
		return res;
    }
};