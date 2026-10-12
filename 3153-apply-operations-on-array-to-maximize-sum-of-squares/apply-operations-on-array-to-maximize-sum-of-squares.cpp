class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> bitCount(31, 0);
        for (int num : nums) {
            for (int i = 0; i < 31; ++i) {
                if ((num >> i) & 1) {
                    bitCount[i]++;
                }
            }
        }
        
        long long ans = 0;
        long long MOD = 1e9 + 7;
        
        for (int i = 0; i < k; ++i) {
            long long current = 0;
            for (int bit = 30; bit >= 0; --bit) {
                if (bitCount[bit] > 0) {
                    current |= (1LL << bit);
                    bitCount[bit]--;
                }
            }
            ans = (ans + current * current) % MOD;
        }
        
        return ans;
    }
};