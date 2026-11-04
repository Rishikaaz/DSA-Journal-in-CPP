class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        multiset<long long> lower, upper;
        long long lower_sum = 0, upper_sum = 0;
        
        vector<long long> min_ops;
        
        for (int i = 0; i < n; ++i) {
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lower_sum += nums[i];
            } else {
                upper.insert(nums[i]);
                upper_sum += nums[i];
            }
            
            if (i >= x) {
                long long out_num = nums[i - x];
                auto it = lower.find(out_num);
                if (it != lower.end()) {
                    lower.erase(it);
                    lower_sum -= out_num;
                } else {
                    it = upper.find(out_num);
                    upper.erase(it);
                    upper_sum -= out_num;
                }
            }
            
            if (lower.size() < upper.size()) {
                long long val = *upper.begin();
                upper.erase(upper.begin());
                upper_sum -= val;
                lower.insert(val);
                lower_sum += val;
            } else if (lower.size() - upper.size() > 1) {
                long long val = *lower.rbegin();
                lower.erase(prev(lower.end()));
                lower_sum -= val;
                upper.insert(val);
                upper_sum += val;
            }
            
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long ops = (median * lower.size() - lower_sum) + (upper_sum - median * upper.size());
                min_ops.push_back(ops);
            }
        }
        
        int m = min_ops.size();
        vector<vector<long long>> dp(k + 1, vector<long long>(m + 1, 1e18));
        for (int i = 0; i <= m; ++i) {
            dp[0][i] = 0;
        }
        
        for (int j = 1; j <= k; ++j) {
            long long min_prev = 1e18;
            for (int i = 1; i <= m; ++i) {
                min_prev = min(min_prev, dp[j - 1][max(0, i - x)]);
                dp[j][i] = min(dp[j][i - 1], min_prev + min_ops[i - 1]);
            }
        }
        
        return dp[k][m];
    }
};