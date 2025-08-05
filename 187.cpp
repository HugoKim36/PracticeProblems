class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        if (s.size() < 10) return ans;
        unordered_map<int, int> seqs;
        array<int, ('T' - 'A') + 1> base;
        base['A' - 'A'] = 0, base['C' - 'A'] = 1;
        base['G' - 'A'] = 2, base ['T' - 'A'] = 3;
        int dna = 0;
        int mask = (1 << 20) - 1;
        for (int i = 0; i < 10; ++i) {
            dna = dna << 2;
            dna |= base[s[i] - 'A'];
        }
        ++seqs[dna];
        for (int i = 10; i < s.size(); ++i) {
            dna = dna << 2;
            dna &= mask;
            dna |= base[s[i] - 'A'];
            ++seqs[dna];
            if (seqs[dna] == 2) ans.push_back(s.substr((i - 9), 10));
        }
        return ans;

    }
};
