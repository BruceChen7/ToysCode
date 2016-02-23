class Solution {
 public:
		const int max_positive_num = 2147483647;
		const int max_negative_num = (-max_positive_num - 1);
		int reverse(int x) {
			if (x > 0){
				return reversePositiveNum(x);
			}
			else {
				x = -1 * x;
				return -1 * reversePositiveNum(x);
			}
		}
	private:
		int reversePositiveNum(int x) {
			if (x >= 0){
				int new_num = 0;

				while (x != 0) {
				    
					int digit = x % 10;
                    
                    //溢出，返回0
					if (new_num > max_positive_num / 10 || new_num < max_negative_num / 10) {
						return 0;
					}
					new_num = 10 * new_num + digit;

					x = x / 10;
				}
				
				return new_num;
			}
			else {
				return 0;
			}
			
		}
};