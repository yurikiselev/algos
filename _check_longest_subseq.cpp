#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 1000;
const int MAX_VAL = 100 * 1000;
const int INF = 100 * 1000 * 1000;

int a[MAXN];

int GetLongestSubseq1(int* a, int MAXN) {
    int dp[MAXN];
    for (int i = 0; i < MAXN; ++i)
        dp[i] = 1;                         // 1, not 0!!!
    for (int i = 1; i < MAXN; ++i)
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);
    
    int res = 0;
    for (int i = 0; i < MAXN; ++i)
        res = max(res, dp[i]);
    return res;
}

int GetLongestSubseq2(int*a, int MAXN) {
    int dp[MAXN];
    for (int i = 0; i < MAXN; ++i) 
        dp[i] = numeric_limits<int>::max();
    dp[0] = numeric_limits<int>::min();
    for (int i = 0; i < MAXN; ++i) {
        int l = 0, r = MAXN - 1;
        int j = MAXN - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (dp[m] > a[i]) {
                j = m;
                r = m - 1;
            } else
                l = m + 1;
        }
        if (dp[j - 1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
        }
    }
    for (int i = MAXN - 1; i >= 0; --i)
        if (dp[i] != numeric_limits<int>::max())
            return i;
    // TODO recover the subsequence
}

bool Test() {
    for (int i = 0; i < MAXN; ++i)
        a[i] = rand() % MAX_VAL;

    int len1 = GetLongestSubseq1(a, MAXN);
    int len2 = GetLongestSubseq2(a, MAXN);
    cerr << "\tlen, len - " << len1 << ' ' << len2 << endl;
    return len1 == len2;
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
