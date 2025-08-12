/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serialized = "";
        if (!root) return "end";
        queue<TreeNode*> bfs({root});
        while (!bfs.empty()) {
            TreeNode* curr = bfs.front();
            bfs.pop();
            if (!curr) {
                serialized.append("null ");
                continue;
            }
            serialized.append((to_string(curr->val) + " "));
            bfs.push(curr->left);
            bfs.push(curr->right);
        }
        serialized.append("end");
        // cout << serialized << '\n';
        return serialized;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "end") return nullptr;
        TreeNode* root = new TreeNode(0);
        istringstream iss(data);
        string val_string;
        iss >> val_string;
        queue<TreeNode*> bfs({root});
        queue<string> values({val_string});
        while (!bfs.empty()) {
            TreeNode* curr = bfs.front();
            bfs.pop();
            val_string = values.front();
            values.pop();
            if (val_string == "null") continue;
            curr->val = stoi(val_string);
            iss >> val_string;
            if (val_string == "end") { break; }
            if (val_string != "null") {
                curr->left = new TreeNode(0);
            }
            bfs.push(curr->left);
            values.push(val_string);
            iss >> val_string;
            if (val_string != "null") {
                curr->right = new TreeNode(0);
            }
            bfs.push(curr->right);
            values.push(val_string);
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
