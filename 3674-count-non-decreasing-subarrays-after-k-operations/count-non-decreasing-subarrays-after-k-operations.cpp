class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        long long cost = 0;
        deque<int> dq;
        
        for (int i = nums.size() - 1, j = nums.size() - 1; i >= 0; --i) {
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                int l = dq.back();
                dq.pop_back();
                int r = dq.empty() ? j + 1 : dq.back();
                cost += (long long)(r - l) * (nums[i] - nums[l]);
            }
            dq.push_back(i);
            
            while (cost > k) {
                cost -= nums[dq.front()] - nums[j];
                if (dq.front() == j) {
                    dq.pop_front();
                }
                --j;
            }
            ans += j - i + 1;
        }
        
        return ans;
    }
};