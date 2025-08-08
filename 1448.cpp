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
    void goodNodes(TreeNode* root, int curr_max, int& count) {
        if (!root) return;
        if (root->val >= curr_max) ++count;
        goodNodes(root->left, max(curr_max, root->val), count);
        goodNodes(root->right, max(curr_max, root->val), count);
    }
    int goodNodes(TreeNode* root) {
        int count = 0;
        goodNodes(root, INT_MIN, count);
        return count;
    }
};
