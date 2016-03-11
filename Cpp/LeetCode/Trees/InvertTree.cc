class Solution {
public: 
TreeNode* invertTree(TreeNode* root) {
		if (root == NULL)
			return NULL;
		else {
			auto left = invertTree(root->left);
			auto right = invertTree(root->right);

			root->left = right;
			root->right = left;
		}
	}
};
