class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        array<int64_t, 60> comps;
        int64_t pairs = 0;
        for (int t : time) {
            if (comps[(t % 60)]) {
                pairs += comps[(t % 60)];
            }
            ++comps[(60 - (t % 60)) % 60];
        }
        return pairs;
    }
};
