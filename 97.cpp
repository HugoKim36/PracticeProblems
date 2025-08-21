class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        const int m = s1.size(), n = s2.size();
        if (s3.size() != (m + n)) return false;
        vector<char> dp(n + 1);
        vector<char> empty(n + 1);
        dp[0] = true;
        for (int j = 1; j <= n && dp[j-1]; ++j) {
            dp[j] = (s2[j-1] == s3[j-1]);
        }
        vector<char> dp_prev(dp);
        for (int i = 1; i <= m; ++i) {
            dp = empty;
            dp[0] = dp_prev[0] && (s1[i-1] == s3[i-1]);
            for (int j = 1; j <= n; ++j) {
                int k = (i + j) - 1;
                if (s3[k] == s1[i-1]) dp[j] = dp_prev[j];
                if (s3[k] == s2[j-1]) dp[j] = dp[j] || dp[j-1];
            }
            dp_prev = dp;
        }
        return dp[n];
    }
};
