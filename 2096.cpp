/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    struct Node {
        TreeNode* ptr = nullptr;
        char dir = '\0';
        int depth = 0;
    };
    string find_path(TreeNode* ancestor, int target) {
        if (!ancestor || ancestor->val == target) return "";
        string path = "";
        stack<Node> dfs({{ancestor, '\0', 0}});
        while (!dfs.empty()) {
            auto curr = dfs.top();
            dfs.pop();
            while (!path.empty() && path.size() >= curr.depth) path.pop_back();
            if (curr.dir) path.push_back(curr.dir);
            if (curr.ptr->val == target) return path;
            if (curr.ptr->left) {
                dfs.push({curr.ptr->left, 'L', curr.depth + 1});
            }
            if (curr.ptr->right) {
                dfs.push({curr.ptr->right, 'R', curr.depth + 1});
            }
        }
        return "";
    }
    TreeNode* lowest_common_ancestor(TreeNode* root, int s, int t) {
        if (!root) return nullptr;
        if (root->val == s || root->val == t) return root;
        TreeNode* left_node = lowest_common_ancestor(root->left, s, t);
        TreeNode* right_node = lowest_common_ancestor(root->right, s, t);
        if (left_node && right_node) return root;
        return (left_node) ? left_node : right_node;
    }
    string getDirections(TreeNode* root, int startValue, int destValue) {
        TreeNode* lca = lowest_common_ancestor(root, startValue, destValue);
        if (lca->val == startValue) {
            return find_path(lca, destValue);
        }
        else if (lca->val == destValue) {
            auto dir = find_path(lca, startValue);
            return string(dir.size(), 'U');
        }
        auto start_path = find_path(lca, startValue);
        auto dir = string(start_path.size(), 'U');
        auto dest_path = find_path(lca, destValue);
        dir.append(dest_path);
        return dir;
    }
};
