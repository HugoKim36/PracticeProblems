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
    int coins(TreeNode* root, int& moves) {
        if (!root) return 0;
        int left_coins = coins(root->left, moves); // coins "given by" left child
        int right_coins = coins(root->right, moves); // coins "given by" right child
        moves += abs(left_coins + right_coins + (root->val - 1));
        return (left_coins + right_coins) + (root->val - 1); 
    }
    int distributeCoins(TreeNode* root) {
        int moves = 0;
        coins(root, moves);
        return moves;
    }
};
