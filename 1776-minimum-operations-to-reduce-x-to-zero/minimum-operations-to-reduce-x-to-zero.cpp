class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        int target = total_sum - x;
        
        if (target < 0) {
            return -1;
        }
        
        if (target == 0) {
            return nums.size();
        }
        
        int max_len = -1;
        int current_sum = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            current_sum += nums[right];
            
            while (current_sum > target) {
                current_sum -= nums[left];
                left++;
            }
            
            if (current_sum == target) {
                max_len = max(max_len, right - left + 1);
            }
        }
        
        return max_len == -1 ? -1 : nums.size() - max_len;
    }
};