class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> ans;
		vector<int> path;
		binaryTreePathsHelper(root, path, ans);
		return ans;

	}
private:
	void binaryTreePathsHelper(TreeNode* root, vector<int>& path, vector<string>& ans) {

		if (root == NULL) {
			return;
		}
		else {
			path.push_back(root->val);
			if (root->left == NULL && root->right == NULL) {
				convertIntVecToPath(path, ans);
				path.pop_back();
			}
			else  {
				if (root->left != NULL && root->right == NULL) {
					binaryTreePathsHelper(root->left, path, ans);
					path.pop_back();
				} else if (root->right != NULL && root->left == NULL) {
					binaryTreePathsHelper(root->right, path, ans);
					path.pop_back();
				}
				else {
					binaryTreePathsHelper(root->left, path, ans);
					binaryTreePathsHelper(root->right, path, ans);
					path.pop_back();
				}
				 
			}
			 


		}

	}
	void convertIntVecToPath(vector<int>& path, vector<string>& ans) {
		int i = 0;
		stringstream ss;
		while (i < path.size()) {
			ss << path[i];
			i++;
			if (i < path.size()) {
				ss << "->";
			}
		}
		ans.push_back(ss.str());
	}
	 
};
