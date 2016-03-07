class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		if (root->left == NULL && root->right == NULL)
			return 1;
		int left_max_depth = maxDepth(root->left);
		int right_max_depth = maxDepth(root->right);

		return std::max(left_max_depth, right_max_depth) + 1;
	}
	 
};