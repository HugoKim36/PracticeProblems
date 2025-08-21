class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        const int mod = 1e9 + 7;
        // let dp[i,j,k] be num schemes after considering i crimes using j members with profit >= k
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
        const vector<vector<int>> empty(n + 1, vector<int>(minProfit + 1));
        if (group[0] <= n) {
            for (int k = 0; k <= min(minProfit, profit[0]); ++k) {
                dp[group[0]][k] = 1;
            }
        }
        dp[0][0] = 1;
        vector<vector<int>> dp_prev(dp);
        for (int i = 1; i < profit.size(); ++i) {
            dp = empty;
            for (int j = 0; j <= n; ++j) {
                for (int k = minProfit; k >= 0; --k) {
                    dp[j][k] += dp_prev[j][k];
                    if (j >= group[i]) {
                        int ways = (dp_prev[j - group[i]][max(0, k - profit[i])] % mod);
                        dp[j][k] = (dp[j][k] % mod + ways) % mod;
                    }
                }
            }
            dp_prev = dp;
        }
        int num = 0;
        for (int j = 0; j <= n; ++j) {
            num = (num + dp[j][minProfit]) % mod;
        }
        return num;
    }
};
