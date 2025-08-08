class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int prefix = 0;
        vector<int> comps(nums.size() + 1);
        comps[0] = 1;
        int count = 0;
        for (int i : nums) {
            prefix += i;
            if (prefix >= goal) count += comps[prefix - goal];
            ++comps[prefix];
        }
        return count;
    }
};
