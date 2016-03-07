class Solution {
public:
   bool isSymmetric(TreeNode* root) {
        if(root == NULL)
            return true;

		if (root->left != NULL  && root->right != NULL) {
			
			if (root->left->val == root->right->val) {

				vector<int> left_in_order_nums;
				vector<int> right_in_order_nums;
				getTreeInOrderNums(root->left, left_in_order_nums);
				getTreeInOrderNums(root->right, right_in_order_nums);
				std::reverse(right_in_order_nums.begin(), right_in_order_nums.end());
				return isTheSame(left_in_order_nums, right_in_order_nums);
			}
			else {
				return false;
			}
		}
		else {
			if (root->left == NULL && root->right == NULL) {
				return true;
			}
			else {
				return false;
			}
		}
		
	}
private:
	void getTreeInOrderNums(TreeNode *root, vector<int>& in_order_nums) {
		if (root == NULL)
			return;
		vector<int> left_nums;
		vector<int> right_nums;
		getTreeInOrderNums(root->left, left_nums);
		left_nums.push_back(root->val);
		getTreeInOrderNums(root->right, right_nums);

		for (auto i : left_nums) {
			in_order_nums.push_back(i);
		}

		for (auto i : right_nums) {
			in_order_nums.push_back(i);
		}

		return;
	}
	bool isTheSame(const vector<int>& in_order, const vector<int>& post_order) {
		if (in_order.size() != post_order.size()) {
			return false;
		}

		else {
			for (int i = 0; i < in_order.size(); i++) {
				if (in_order[i] != post_order[i])
					return false;
			}
			return true;
		}
	}
	 
};