class Solution {
public:
bool is_match(vector<vector<int8_t>>& dp, const string& s, const string& p, int i, int j) {
        if (dp[i][j] != -1) {
            if (i == 0 && j > 0) {
                return dp[i][j] && is_match(dp, s, p, i, j - 1);
            }
            return dp[i][j];
        }
        dp[i][j] = false;
        if (s[i-1] == p[j-1] || p[j-1] == '?') {
            dp[i][j] = is_match(dp, s, p, i - 1, j - 1);
        }
        else if (p[j-1] == '*') {
            dp[i][j] = is_match(dp, s, p, i, j - 1) || is_match(dp, s, p, i - 1, j);
        }
        return dp[i][j];
    }
    bool isMatch(string s, string p) {
        vector<vector<int8_t>> dp(s.size() + 1, vector<int8_t>(p.size() + 1, -1));
        dp[0][0] = true;
        for (int j = 1; j <= p.size(); ++j) {
            dp[0][j] = (p[j-1] == '*');
        }
        for (int i = 1; i <= s.size(); ++i) {
            dp[i][0] = false;
        }
        dp[s.size()][p.size()] = is_match(dp, s, p, s.size(), p.size());
        return dp[s.size()][p.size()];
    }
};
