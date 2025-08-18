class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int max_len = 1;
        int max_diff = *ranges::max_element(nums) - *ranges::min_element(nums);
        vector<vector<int>> dp(nums.size(), vector<int>((max_diff * 2) + 1, 0));
        for (int j = 1; j < nums.size(); ++j) {
            for (int i = 0; i < j; ++i) {
                int diff = (nums[j] - nums[i]) + max_diff;
                if (dp[i][diff] == 0) dp[j][diff] = 2;
                else dp[j][diff] = dp[i][diff] + 1;
                max_len = max(max_len, dp[j][diff]);
            }
        }
        return max_len;
    }
};
