class Solution {
public:
    class MedianFinder {
    public:
        MedianFinder() { }
        
        void push(int num) {
            if (bottom_half.empty()) {
                if (!top_half.empty() && num > *top_half.begin()) {
                    int smaller = *top_half.begin();
                    top_half.erase(top_half.begin());
                    bottom_half.insert(smaller);
                    top_half.insert(num);
                    return;
                }
                bottom_half.insert(num);
                return;
            }
            else if (top_half.empty()) {
                if (num < *prev(bottom_half.end())) {
                    int bigger = *prev(bottom_half.end());
                    top_half.insert(bigger);
                    bottom_half.erase(prev(bottom_half.end()));
                    bottom_half.insert(num);
                }
                else {
                    top_half.insert(num);
                }
                return;
            }
            bottom_half.insert(num);
            while (top_half.size() < (size() / 2)) {
                int bigger = *prev(bottom_half.end());
                top_half.insert(bigger);
                bottom_half.erase(prev(bottom_half.end()));
            }
            while (*prev(bottom_half.end()) > *(top_half.begin())) {
                int bottom = *prev(bottom_half.end());
                int top = *(top_half.begin());
                bottom_half.erase(prev(bottom_half.end()));
                top_half.erase(top_half.begin());
                bottom_half.insert(min(bottom, top));
                top_half.insert(max(bottom, top));
            }
        }
        
        double find_median() const {
            if (size() % 2) { // odd
                return *prev(bottom_half.end());
            }
            else return (static_cast<int64_t>(*prev(bottom_half.end()))
                         + static_cast<int64_t>(*top_half.begin())) / 2.0;
        }

        void erase(int num) {
            if (num <= *prev(bottom_half.end())) {
                auto it = bottom_half.lower_bound(num);
                bottom_half.erase(it);
            }
            else {
                auto it = top_half.lower_bound(num);
                top_half.erase(it);
            }
        }
    private:
        size_t size() const {
            return bottom_half.size() + top_half.size();
        }
        multiset<int> bottom_half;
        multiset<int> top_half;
    };
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        MedianFinder window;
        for (int i = 0; i < k; ++i) {
            window.push(nums[i]);
        }
        medians.push_back(window.find_median());
        for (int i = k; i < nums.size(); ++i) {
            window.erase(nums[i - k]);
            window.push(nums[i]);
            medians.push_back(window.find_median());
        }
        return medians;
    }
};
