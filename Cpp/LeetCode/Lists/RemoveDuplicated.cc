class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
		std::map<int, bool> value;
		ListNode* previous_i = NULL;

		for (auto i = head; i != NULL; ) {
			
			
			if (value.find(i->val) == value.end()) {
				value.insert(std::make_pair(i->val, true));
				previous_i = i;
				i = i->next;
			}
			else {
				auto i_next = i->next;
				previous_i->next = i_next;
				delete i;
				 
				i = i_next;
			}
			
		}
		return head;
	}
};