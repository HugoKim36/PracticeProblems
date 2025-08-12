class Solution {
public:
    const string& find_set(unordered_map<string, string>& reps, const string& s) {
        if (reps[s] == s) return s;
        return reps[s] = find_set(reps, reps[s]);
    }
    void union_set(unordered_map<string, string>& reps, const string& s, const string& t) {
        reps[find_set(reps, s)] = find_set(reps, t);
    }
    bool similar(string_view s, string_view t) {
        int diffs = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != t[i]) ++diffs;
            if (diffs >= 3) return false;
        }
        return true;
    }
    int numSimilarGroups(vector<string>& strs) {
        unordered_map<string, string> reps;
        for (const auto& s : strs) reps[s] = s;
        int num_groups = reps.size();
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = i + 1; j < strs.size(); ++j) {
                if (strs[i] == strs[j]) continue;
                if (similar(strs[i], strs[j]) && find_set(reps, strs[i]) != find_set(reps, strs[j])) {
                    --num_groups;
                    union_set(reps, strs[i], strs[j]);
                }
            }
        }
        return num_groups;
    }
};
