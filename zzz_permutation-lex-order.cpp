// http://www.geeksforgeeks.org/lexicographic-permutations-of-string/

/*
	Steps to generate the next higher permutation:
		1. Take the previously printed permutation and find the rightmost character in it, which is smaller than its next character. Let us call this character as ‘first character’.

		2. Now find the ceiling of the ‘first character’. Ceiling is the smallest character on right of ‘first character’, which is greater than ‘first character’. Let us call the ceil character as ‘second character’.

		3. Swap the two characters found in above 2 steps.

		4. Sort the substring (in non-decreasing order) after the original index of ‘first character’.

	Let us consider the string “ABCDEF”. Let previously printed permutation be “DCFEBA”. The next permutation in sorted order should be “DEABCF”. Let us understand above steps to find next permutation. The ‘first character’ will be ‘C’. The ‘second character’ will be ‘E’. After swapping these two, we get “DEFCBA”. The final step is to sort the substring after the character original index of ‘first character’. Finally, we get “DEABCF”.
*/

class Solution {
public:
    vector<vector<int> > permute(vector<int>& a) {
    	sort(a.begin(), a.end());
		
		vector< vector<int> > res;
		int n = a.size();
		while (true) {
			res.push_back(a);
			int first = -1;
			for (int i = n - 2; i >= 0; --i)
				if (a[i] < a[i + 1]) {
					first = i;
					break;
				}
			
			if (first == -1)
				break;
			
			int second = -1;
			for (int i = first + 1; i < n; ++i)
				if (a[first] < a[i] && 
					(second == -1 || a[second] > a[i]))
					second = i;
			swap(a[first], a[second]);
			sort(a.begin() + first + 1, a.end());
		}
		return res;
    }
};