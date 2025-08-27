class Solution {
public:
    struct Counter {
        Counter(int k_in) : elts(vector<int>(k_in)) { }
        vector<int> elts;
        size_t num_elts = 0;
        size_t size() const {
            return num_elts;
        }
        void inc(int k) {
            if (++elts[k] == 1) ++num_elts;
        }
        void dec(int k) {
            if (--elts[k] == 0) --num_elts;
        }
    };
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> range = {-1, -1};
        int k = nums.size();
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> min_pq;
        for (int i = 0; i < k; ++i) {
            auto it = unique(nums[i].begin(), nums[i].end());
            nums[i].erase(it, nums[i].end());
            min_pq.push({nums[i][0], i});
        }
        vector<int> curr_index(k);
        vector<pair<int,int>> merged;
        while (!min_pq.empty()) {
            auto [num, idx] = min_pq.top();
            min_pq.pop();
            merged.push_back({num, idx});
            if (curr_index[idx] + 1 < nums[idx].size()) {
                min_pq.push({nums[idx][++curr_index[idx]], idx});
            }
        }
        int i = 0;
        Counter included(k);
        for (int j = 1; j <= merged.size(); ++j) {
            included.inc(merged[j-1].second);
            while (i < j && included.size() >= k) {
                int old_diff = (range[0] == -1) ? INT_MAX : (range[1] - range[0]);
                if (merged[j-1].first - merged[i].first < old_diff) {
                    range[0] = merged[i].first;
                    range[1] = merged[j-1].first;
                }
                included.dec(merged[i].second);
                ++i;
            }
        }
        return range;
    }
};
