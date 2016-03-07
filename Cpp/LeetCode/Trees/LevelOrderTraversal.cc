class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> ans;
		queue<TreeNodeInfo> tree_node;
		vector<TreeNodeValue> node_value;

		if (root == NULL) {
			return ans;
		}
		else {

			TreeNodeInfo node_info{1, root};
			tree_node.push(node_info);
			node_value.push_back({ 1, root->val });
				 

			while (!tree_node.empty()) {
				auto first_tree_node = tree_node.front();
				auto new_level = first_tree_node.level + 1;
				if (first_tree_node.node->left != NULL) {
					
					TreeNodeInfo node_info(new_level, first_tree_node.node->left);
					TreeNodeValue value{ new_level, first_tree_node.node->left->val };
					tree_node.push(node_info);
					node_value.push_back(value);
				}

				if (first_tree_node.node->right != NULL) {
					 
					TreeNodeInfo node_info(new_level, first_tree_node.node->right);
					TreeNodeValue value{ new_level, first_tree_node.node->right->val };
					tree_node.push(node_info);
					node_value.push_back(value);
				}

				tree_node.pop();
			}
			return mergeNodeValue(node_value);
		}
	}
private:
	struct TreeNodeInfo {
		int level;
		TreeNode *node;
		TreeNodeInfo(int level, TreeNode* node) : level(level), node(node) {

		}
	};

	struct TreeNodeValue {
		int value;
		int level;
		TreeNodeValue(int level, int value) : value(value), level(level) {

		}
	};

	vector<vector<int>> mergeNodeValue(vector<TreeNodeValue> node_value) {

		vector<vector<int>> ans;

		int i = node_value.size()-1;
		while (i >= 0) {
			vector<int> elem;
			auto value = node_value[i];
			elem.push_back(value.value);

			int j = i-1;
			while (j >= 0 && node_value[j].level == value.level) {
				elem.push_back(node_value[j].value);
				j--;
				
			}
			std::reverse(elem.begin(), elem.end());
			ans.push_back(elem);
			i = j;
		}
		return ans;
	}
};