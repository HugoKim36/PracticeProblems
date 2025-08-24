class Solution {
public:
    bool read_line(vector<string>& words, int maxWidth, string& line, int& i) {
        line = words[i++];
        bool need_trailing_space = (line.size() < maxWidth);
        while (i < words.size()) {
            if (line.size() + 1 + words[i].size() <= maxWidth) {
                line.append(" " + words[i++]);
                need_trailing_space = false;
            } // trailing ws only for one-word lines (and the last line)
            else break;
        }
        if (need_trailing_space) {
            line.append(string(maxWidth - line.size(), ' '));
        }
        return (i != words.size()); // return false if we read the last line
    }

    void add_spaces(string& line, int maxWidth) {
        while (line.size() < maxWidth) {
            for (int pos = 0; pos < line.size(); ++pos) {
                if (line[pos] != ' ') continue;
                line.insert(pos, 1, ' ');
                if (line.size() == maxWidth) return;
                while (line[pos + 1] == ' ') ++pos;
            }
        }
    }

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> justified;
        string line;
        int i = 0; // index of current word
        while (read_line(words, maxWidth, line, i)) {
            add_spaces(line, maxWidth); // not called on last line of text
            justified.push_back(line);
        }
        if (line.size() < maxWidth) { // handle special spacing for last line
            line.append(string(maxWidth - line.size(), ' '));
        }
        justified.push_back(line);
        return justified;
    }
};
