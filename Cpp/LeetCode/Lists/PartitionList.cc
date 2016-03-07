class Solution {
public:
 ListNode* partition(ListNode* head, int x) {
		if (head == NULL)
			return NULL;

		auto new_head = head;
		while (isOrdered(new_head, x) == false) {
			auto last_small = findLastSmallerIndex(new_head, x);

			if (last_small == NULL) {
				getNewHead(new_head, x);
			}
			else {
				auto last_big = findLarstBiggerIndex(last_small->next, x);
				auto last_small_next = last_small->next;
				auto last_big_next_next = last_big->next->next;
				auto last_big_reserve_next = last_big->next;

				last_small->next = last_big->next;
				last_big->next = last_big_next_next;
				last_big_reserve_next->next = last_small_next;

			}
		}
		return new_head;
	}
	
private:
	void getNewHead(ListNode* &head, int x) {
		auto last_big = findLarstBiggerIndex(head, x);
		auto small = last_big->next;
		auto head_next = head->next;
		
		if (small != NULL) {
			auto small_next = small->next;

			last_big->next = small_next;
			small->next = head;
			head = small;
		}
	}
	ListNode* findLastSmallerIndex(ListNode* head, int value) {
		ListNode *ans = NULL;
		for (auto i = head; i != NULL; i = i->next) {
			if (i->val < value) {
				ans = i;
			}
			else {
				break;
			}
		}
		return ans;
	}

	ListNode* findLarstBiggerIndex(ListNode* head, int value) {
		ListNode *ans = NULL;
		for (auto i = head; i != NULL; i = i->next) {
			if (i->val >= value) {
				ans = i;
			}
			else {
				break;
			}
		}
		return ans;
	}
	bool isOrdered(ListNode *head, int val) {
		auto i = head;
		auto last_small_index = findLastSmallerIndex(head, val);
		ListNode* big_head;
		if (last_small_index == NULL) {
			big_head = head;
		}
		else {
			big_head = last_small_index->next;
		}
		auto last_bigger_indx = findLarstBiggerIndex(big_head, val);
		if (last_bigger_indx == NULL || last_bigger_indx->next == NULL)
			return true;
		else
			return false;
	}
 
};