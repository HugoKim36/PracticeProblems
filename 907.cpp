class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int64_t sum = 0;
        stack<int> indices;
        for (int i = 0; i < arr.size(); ++i) {
            while (!indices.empty() && arr[i] <= arr[indices.top()]) {
                int curr = indices.top();
                indices.pop();
                int left_bound = indices.empty() ? -1 : indices.top();
                int subarrays = (curr - left_bound) * (i - curr);
                sum = (sum + (subarrays * arr[curr])) % MOD;
            }
            indices.push(i);
        }
        while (!indices.empty()) { // nothing smaller to the right
            int curr = indices.top();
            indices.pop();
            int left_bound = indices.empty() ? -1 : indices.top();
            int64_t subarrays = (curr - left_bound) * (arr.size() - curr);
            sum = (sum + (subarrays * arr[curr])) % MOD;
        }
        return sum;
    }
};
