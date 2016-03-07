class Solution {
    
    public:
       vector<int> twoSum(vector<int>& nums, int target) {
		int i = 0;
		int size = nums.size();
		vector<int> ans;

		for (int i = 0; i < size; i++) {
			
		        int difference = target - nums[i];
				int j = findAnother(difference, i+1, nums);

				if (j != -1) {
					ans.push_back(i);
					ans.push_back(j);
				}
			
		}
		return ans;
	}
private:
	int findAnother(int difference, int begin, const vector<int>& nums) {
		for (int i = begin; i < nums.size(); i++) {
			if (nums[i] == difference)
				return i;
		}
		return -1;
	}
};