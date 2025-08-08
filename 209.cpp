class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int min_length = INT_MAX;
        int prefix = nums[0];
        int left = 0;
        for (int i = 1; i <= nums.size(); ++i) {
            while (prefix >= target) {
                min_length = min(min_length, i - left);
                prefix -= nums[left++];
            }
            if (i < nums.size()) prefix += nums[i];
        }
        return (min_length == INT_MAX) ? 0 : min_length;
    }
};
