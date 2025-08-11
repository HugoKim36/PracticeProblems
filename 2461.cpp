class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long max_sum = 0;
        unordered_map<int, int> counts;
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
            ++counts[nums[i]];
        }
        if (counts.size() == k) max_sum = sum;
        
        for (int i = k; i < nums.size(); ++i) {
            --counts[nums[i - k]];
            if (counts[nums[i - k]] == 0) counts.erase(nums[i - k]);
            sum -= nums[i - k];

            ++counts[nums[i]];
            sum += nums[i];
            if (counts.size() == k) {
                max_sum = max(max_sum, sum);
            }
        }
        return max_sum;
    }
};
