/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
			
			ListNode *head = NULL;
			ListNode *tail = NULL;
			
			//进位
			int carry = 0;

			while (l1 != NULL && l2 != NULL) {
				int value1 = getValueAndMoveNext(l1);
				int value2 = getValueAndMoveNext(l2);

				int sum = value1 + value2 + carry;
				if (head == NULL) {
					head = new ListNode(sum % 10);
					addListNodeToTailAndUpdateTail(head, tail);
				}
				else {
					ListNode *h = new ListNode(sum % 10);
					addListNodeToTailAndUpdateTail(h, tail);
				}

				carry = sum / 10;
			}



			while (l1 != NULL) {
				int l1_value = getValueAndMoveNext(l1);
				int sum = carry + l1_value;
				ListNode *h = new ListNode(sum % 10);
				addListNodeToTailAndUpdateTail(h, tail);
				
				carry = sum / 10;
			}
			while (l2 != NULL) {
				int l2_value = getValueAndMoveNext(l2);
				int sum = carry + l2_value;
				ListNode *h = new ListNode(sum % 10);
				addListNodeToTailAndUpdateTail(h, tail);

				carry = sum / 10;
			}

			if (carry > 0) {
				ListNode *h = new ListNode(carry % 10);
				addListNodeToTailAndUpdateTail(h, tail);
			}
			 
			return head;
			
		}
	 private:
		 int getValueAndMoveNext(ListNode* &l1) {
			 if (l1 != NULL) {
				 int value = l1->val;
				 l1 = l1->next;
				 return value;
			 }
			 else {
				 return 0;
			 }
		 }

		 //将L加到tail的后面, 并更新tail指针
		 void addListNodeToTailAndUpdateTail(ListNode *l, ListNode * &tail) {
			 if (tail != NULL  && l != NULL) {
				 tail->next = l;
				 tail = l;
			 }
			 else  {
				 tail = l;
			 }
		 }

};