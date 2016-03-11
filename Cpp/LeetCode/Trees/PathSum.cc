class Solution {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		auto all_path = binaryTreePaths(root);
		for (auto path : all_path) {
			auto path_sum = computePathSum(path);

			if (path_sum == sum)
				return true;
		}
		return false;
	}

	
private:
	int computePathSum(vector<int>& path) {
		int sum = 0;

		for (auto i : path) {
			sum += i;
		}
		return sum;
	}
	vector<vector<int>> binaryTreePaths(TreeNode* root) {

		vector<int> path;
		vector<vector<int>> all_path;
		binaryTreePathsHelper(root, path, all_path);
		return all_path;

	}
	void binaryTreePathsHelper(TreeNode* root, vector<int>& path, vector<vector<int>>& all_path) {

		if (root == NULL) {
			return;
		}
		else {
			path.push_back(root->val);
			if (root->left == NULL && root->right == NULL) {
				all_path.push_back(path);
				path.pop_back();
			}
			else  {
				if (root->left != NULL && root->right == NULL) {
					binaryTreePathsHelper(root->left, path, all_path);
					path.pop_back();
				}
				else if (root->right != NULL && root->left == NULL) {
					binaryTreePathsHelper(root->right, path, all_path);
					path.pop_back();
				}
				else {
					binaryTreePathsHelper(root->left, path, all_path);
					binaryTreePathsHelper(root->right, path, all_path);
					path.pop_back();
				} 
			} 
		}

	} 
};
