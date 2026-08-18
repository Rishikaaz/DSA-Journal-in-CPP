class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        if (k == 1) {
            int ans = -1;
            for (auto& [num, freq] : count) {
                if (freq == 1) {
                    ans = max(ans, num);
                }
            }
            return ans;
        }
        int ans = -1;
        if (count[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }
        if (count[nums.back()] == 1) {
            ans = max(ans, nums.back());
        }
        return ans;
    }
};