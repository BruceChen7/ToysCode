class Solution {
public:
	bool isValidBST(TreeNode* root) {
		if (root != NULL) {
			if (isValidBST(root->left) == false) {
				return false;
			}
			else if (isValidBST(root->right) == false) {
				return false;
			}
			else {

				if (root->left != NULL) {
					int left_largest_val = getLeftLargestValue(root->left);

					if (root->val <= left_largest_val) {
						return false;
					}


				}

				if (root->right != NULL) {

					int right_least_val = getRightLeastValue(root->right);
					if (root->val >= right_least_val) {
						return false;
					}
				}

				return true;

			}
		}
		else {
			return true;
		}
	}
private:
	int getLeftLargestValue(TreeNode* root) {

		while (root->right!= NULL) {
			root = root->right;
		}
		return root->val;
	}

	int getRightLeastValue(TreeNode* root) {
		while (root->left != NULL) {
			root = root->left;
		}
		return root->val;
	}
};
