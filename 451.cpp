class Solution {
public:
    template <typename BidirIt, typename Compare = std::less<>> 
    void freq_sort(BidirIt first, BidirIt last, Compare comp = Compare{}) {
        using T = std::decay_t<decltype(*first)>; // dereferenced iterator type
        uint32_t max_freq = 1;
        std::unordered_map<T, uint32_t> item_freq;
        for (auto it = first; it != last; std::advance(it, 1)) {
            max_freq = max(++item_freq[*it], max_freq);
        }
        std::vector<std::vector<T>> bucket(max_freq + 1);
        for (const auto& [item, freq] : item_freq) {
            bucket[freq].push_back(item);
        }
        int start_pos = comp(0, max_freq) ? 0 : max_freq;
        int end_pos = (start_pos == 0) ? max_freq + 1 : -1;
        int dir = comp(-1, 1) ? 1 : -1;
        for (int32_t i = start_pos; i != end_pos; i += dir) { // for each freq
            for (const auto& item : bucket[i]) { 
                for (int j = 0; j < i; ++j) {
                    *first = item;
                    std::advance(first, 1);
                }
            }
        }
    }
    
    string frequencySort(string s) {
        freq_sort(s.begin(), s.end(), greater<>());
        return s;
    }
};
