class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);
        for (int i = 0; i < n; ++i) {
            squares[i] = (long long)nums[i] * nums[i];
        }
        sort(squares.rbegin(), squares.rend());
        
        int k = (n + 1) / 2;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (i < k) {
                ans += squares[i];
            } else {
                ans -= squares[i];
            }
        }
        return ans;
    }
};