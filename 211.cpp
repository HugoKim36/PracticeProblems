struct TrieNode {
    array<TrieNode*, 26> children = {};
    bool is_word = false;
    ~TrieNode() {
        for (auto& child : children) {
            delete child;
            child = nullptr;
        }
    }
};

class Trie {
public:
    Trie() : root(new TrieNode{}) { }
    ~Trie() { delete root; }
    void insert(string_view word) {
        if (!root->children[word[0] - 'a']) {
            root->children[word[0] - 'a'] = new TrieNode{};
        }
        insert_impl(word, root->children[word[0] - 'a'], 0);
    }
    bool find(string_view word) const {
        if (word[0] == '.') {
            for (int i = 0; i < 26; ++i) {
                if (find_impl(word, root->children[i], 0)) {
                    return true;
                }
            }
            return false;
        }
        return find_impl(word, root->children[word[0] - 'a'], 0);
    }
private:
    void insert_impl(string_view word, TrieNode*& root, int depth) {
        if (depth == word.size() - 1) {
            root->is_word = true;
            return;
        }
        if (!root->children[word[depth + 1] - 'a']) {
            root->children[word[depth + 1] - 'a'] = new TrieNode{};
        }
        insert_impl(word, root->children[word[depth + 1] - 'a'], depth + 1);
    }

    bool find_impl(string_view word, TrieNode*& root, int depth) const {
        if (!root) return false;
        if (depth == word.size() - 1) {
            return root->is_word;
        }
        if (word[depth + 1] == '.') {
            for (int i = 0; i < 26; ++i) {
                if (find_impl(word, root->children[i], depth + 1)) {
                    return true;
                }
            }
            return false;
        }
        return find_impl(word, root->children[word[depth + 1] - 'a'], depth + 1);
    }

    TrieNode* root = nullptr;
};

class WordDictionary {
public:
    WordDictionary() { }
    
    void addWord(string word) {
        prefix_tree.insert(word);
    }
    
    bool search(string word) {
        return prefix_tree.find(word);
    }
private:
    Trie prefix_tree;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
