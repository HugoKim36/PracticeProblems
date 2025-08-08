class Solution {
public:
    string removeDuplicates(string s, int k) {
        deque<pair<char, int>> distinct;
        string ans;
        for (char c : s) {
            if (!distinct.empty() && distinct.back().first == c) {
                
                distinct.push_back({c, distinct.back().second + 1});
            }
            else distinct.push_back({c, 1});
            if (!distinct.empty() && distinct.back().second >= k) {
                for (int i = 0; i < k; ++i) distinct.pop_back();
            }
        }
        while (!distinct.empty()) {
            ans += distinct.front().first;
            distinct.pop_front();
        }
        return ans;
    }
};
