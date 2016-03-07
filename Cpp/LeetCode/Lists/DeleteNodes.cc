class Solution {
public:
   void deleteNode(ListNode* node) {
		if (node == NULL) {
			return;
		}
		node->val = node->next->val;
		auto tmp = node->next;
		node->next = tmp->next;
		delete tmp;
	 
	}
};