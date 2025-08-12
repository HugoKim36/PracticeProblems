class Solution {
public:
    struct LetterMap {
        array<int, 26> freq;
        int& operator[](char c) { return freq[c - 'A']; }
        int max_freq() const {
            return *max_element(freq.begin(), freq.end());
        }
    };
    int characterReplacement(string s, int k) {
        if (s.size() <= k + 1) return s.size();
        int i = 0;
        int longest = (k + 1);
        LetterMap count;
        for (int j = 1; j <= k + 1; ++j) {
            ++count[s[j-1]];
        }
        for (int j = k + 2; j <= s.size(); ++j) {
            ++count[s[j-1]];
            if ((j - i) - count.max_freq() <= k) {
                longest = max(longest, (j - i));
            }
            else {
                for (; i < (j - longest); ++i) {
                    if (count[s[i]] > 0) --count[s[i]];
                }
            }
        }
        return longest;
    }
};
