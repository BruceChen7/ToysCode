class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		int length = getLength(head);
		
		if (head == NULL || k == length || k == 0) {
			return head;
		}
		else {
			k = k % length;

			if (k == 0)
				return head;
			auto p = getKthNode(head, k);
			auto rotate_head = head;
			ListNode* previous_rotate_head = NULL;
			ListNode* previous_i = NULL;
			
			//make sure p is not NULL
			auto i = p;
			for (; i->next != NULL; i = i->next) {
				previous_i = i;
				previous_rotate_head = rotate_head;
				rotate_head = rotate_head->next;
			}
			
			previous_rotate_head->next = NULL;
			i->next = head;

			return rotate_head;
		}
			
		
	}
private:
	int getLength(ListNode *head) {
		int length = 0;
		while (head != NULL) {
			length++;
			head = head->next;
		}
		return length;
	}

	ListNode* getKthNode(ListNode* head, int k) {
		int cnt = 0;

		for (auto i = head; i != NULL; i = i->next) {
			cnt++;
			if (cnt == k)
				return i;
		}
		return NULL;
	}
};