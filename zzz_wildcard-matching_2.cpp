// recursive solution
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
    	if (*s == '\0' && *p == '\0')
			return true;
		if (*p == '\0')
			return false;
		if (*s == '\0') {
			if (*p == '*')
				return isMatch(s, p + 1);
			return false;
		}
		if (*s == *p || *p == '?')
			return isMatch(s + 1, p + 1);
		if (*p == '*') {
            // speadup a little bit
    	    //if (*(p + 1) == '*')
            //    return isMatch(s, p + 1);
			return isMatch(s, p + 1) || isMatch(s + 1, p);
		}
		return false;
    }
};

// http://discuss.leetcode.com/questions/222/wildcard-matching
// cool DP solution
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int n = strlen(s);
		int m = strlen(p);
		{ // This is a stupido optimization
			int chars = 0;
            for (int i = 0; i < m; ++i)
                if (p[i] != '*')
                    ++chars;
			if (chars > n)
				return false;
		}
		vector< vector<int> > dp(2, vector<int>(n + 1, 0));
		dp[0][0] = 1;
		int cur = 0;
		for (int i = 0; i < m; ++i) {
			int nxt = cur ^ 1;
			dp[nxt].assign(n + 1, 0); // don't forget!
			if (p[i] == '*' && dp[cur][0] == 1)
				dp[nxt][0] = 1; // and this!
			bool goodAst = dp[cur][0];
			for (int j = 0; j < n; ++j) {
				goodAst |= dp[cur][j + 1]; // Taht's OR!
				if (s[j] == p[i] || p[i] == '?')
					dp[nxt][j + 1] = dp[cur][j];
				else
                    if (p[i] == '*')
					    dp[nxt][j + 1] = goodAst;
			}
			cur = nxt;
		}
		return dp[cur].back();
    }
};