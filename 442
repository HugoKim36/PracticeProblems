class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> duplicates;
        int i = 0;
        while (i < nums.size()) {
            int correct = nums[i] - 1;
            if (nums[i] == nums[correct]) ++i;
            else swap(nums[i], nums[correct]);
        }
        for (int i = 0; i < nums.size(); ++i) {
            int correct = nums[i] - 1;
            if (i != correct) duplicates.push_back(nums[i]);
        }
        return duplicates;
    }
};
