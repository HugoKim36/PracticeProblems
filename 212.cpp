struct TrieNode {
    bool is_word = false;
    vector<TrieNode*> children;
    TrieNode() {
        children = vector<TrieNode*>(26, nullptr);
    }
    ~TrieNode() { 
        for (int i = 0; i < 26; ++i) {
            delete children[i];
            children[i] = nullptr;
        }
    }
};
class Trie {
public:
    Trie() : root(new TrieNode{}) { }
    void insert(const string& word) {
        if (!root->children[word[0] - 'a']) {
            root->children[word[0] - 'a'] = new TrieNode{};
        }
        insert_impl(word, 0, root->children[word[0] - 'a']);
    }

    bool has_prefix(const string& word) const {
        return has_prefix_impl(word, 0, root->children[word[0] - 'a']);
    }

    void erase(const string& word) {
        erase_impl(word, 0, root->children[word[0] - 'a']);
    }

    ~Trie() { delete root; }
private:
    void insert_impl(const string& word, int depth, TrieNode* curr) {
        if (depth == word.size() - 1) {
            curr->is_word = true;
            return;
        }
        if (!curr->children[word[depth + 1] - 'a']) {
            curr->children[word[depth + 1] - 'a'] = new TrieNode{};
        }
        insert_impl(word, depth + 1, curr->children[word[depth + 1] - 'a']);
    }

    bool has_prefix_impl(const string& word, int depth, TrieNode* curr) const {
        if (!curr) return false;
        if (depth == word.size() - 1) {
            for (auto& ptr : curr->children) {
                if (ptr) return true;
            }
            return curr->is_word;
        }
        return has_prefix_impl(word, depth + 1, curr->children[word[depth + 1] - 'a']);
    }

    void erase_impl(const string& word, int depth, TrieNode*& curr) {
        if (!curr) return;
        if (depth < word.size() - 1) {
            erase_impl(word, depth + 1, curr->children[word[depth + 1] - 'a']);
        }
        curr->is_word = false;
        for (auto& child : curr->children) {
            if (child) return;
        }
        delete curr;
        curr = nullptr;
    }

    TrieNode* root = nullptr;
};

class Solution {
public:
    array<int8_t, 4> row_dirs = {1, 0, -1, 0};
    array<int8_t, 4> col_dirs = {0, 1, 0, -1};
    void dfs(vector<vector<char>>& board, unordered_set<string>& word_bank, 
             vector<string>& search, string& curr, int row, int col, Trie& t) {
        if (word_bank.contains(curr)) {
            search.push_back(curr);
            t.erase(curr);
            word_bank.erase(curr);
        }
        if (!t.has_prefix(curr)) return;
        for (int i = 0; i < 4; ++i) {
            int n_row = row + row_dirs[i];
            int n_col = col + col_dirs[i];
            if (n_row >= 0 && n_row < board.size() 
                    && n_col >= 0 && n_col < board[0].size()) {
                if (board[n_row][n_col] == ' ') continue;
                char next_letter = board[n_row][n_col];
                board[n_row][n_col] = ' ';
                curr += next_letter;
                dfs(board, word_bank, search, curr, n_row, n_col, t);
                curr.pop_back();
                board[n_row][n_col] = next_letter;
            }
        }
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_set<string> word_bank(words.begin(), words.end());
        Trie t;
        for (const auto& w : words) { t.insert(w); }
        vector<string> search;
        string curr = "";
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                char next_letter = board[i][j];
                curr += next_letter;
                board[i][j] = ' ';
                dfs(board, word_bank, search, curr, i, j, t);
                board[i][j] = next_letter;
                curr = "";
            }
        }
        return search;
    }
};
