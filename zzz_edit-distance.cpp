class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        if (n == 0 || m == 0)
            return n + m;

        vector< vector<int> > dp(n + 1, vector<int>(m + 1, n + m)); // (n + 1) * (m + 1) !!!        
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                if (i == 0 || j == 0)
                    dp[i][j] = i + j;
				else {
                    int add = word1[i - 1] != word2[j - 1]; // !!!
					dp[i][j] = dp[i - 1][j - 1] + add;
					dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
					dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
				}
        return dp[n][m];
    }
};