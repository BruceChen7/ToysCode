class Solution {
 public:

	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		int a_length = getLength(headA);
		int b_length = getLength(headB);

		int bigger = std::max(a_length, b_length);
		bool is_a_bigger = false;

		if (bigger == a_length) {
			is_a_bigger = true;
		}

		if (is_a_bigger) {
			auto head_a = getListNodeHead(headA, a_length - b_length+1);
			return getCommonListNodeHead(head_a, headB);
		}
		else {
			auto head_b = getListNodeHead(headB, b_length - a_length + 1);
			return getCommonListNodeHead(head_b, headA);
		}
			
	}
private:

	ListNode* getCommonListNodeHead(ListNode* a, ListNode* b) {
		while (a != NULL && b != NULL) {
			if (a->val == b->val) {
				return a;
			}
			else {
				a = a->next;
				b = b->next;
			}
		}
		
		return NULL;
	}

	ListNode* getListNodeHead(ListNode *head, int index) {
		 

		int i = 0;
		while (head) {
			i++;
			if (i == index) {
				return head;
			}
			else {
				head = head->next;
			}
		}
	}
	int getLength(ListNode *head) {
		int length = 0;
		while (head != NULL) {
			length++;
			head = head->next;
		}
		return length;
	}
};