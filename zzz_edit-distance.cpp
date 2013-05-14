    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (word1.empty())
            return word2.size();
        if (word2.empty())
            return word1.size();

        int n = word1.size();
        int m = word2.size();
        vector< vector<int> > dp; // (n + 1) * (m + 1) !!!
        dp.resize(n + 1);
        for (size_t i = 0; i < dp.size(); ++i)
            dp[i].resize(m + 1, n + m);
        
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i == 0 && j == 0)
    				dp[i][j] = 0;
				else {
					if (i == 0)
						dp[i][j] = j;
					else {
						if (j == 0)
							dp[i][j] = i;
						else {
                            int add = word1[i - 1] != word2[j - 1]; // !!!
							dp[i][j] = dp[i - 1][j - 1] + add;
							dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
							dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
						}
					}
				}
            }
        }
        return dp[n][m];
    }