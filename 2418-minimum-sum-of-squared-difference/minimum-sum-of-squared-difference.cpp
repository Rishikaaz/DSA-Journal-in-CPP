class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long total_k = (long long)k1 + k2;
        vector<long long> count(100001, 0);
        long long total_diff = 0;
        
        for (int i = 0; i < n; ++i) {
            int diff = abs(nums1[i] - nums2[i]);
            count[diff]++;
            total_diff += diff;
        }
        
        if (total_diff <= total_k) {
            return 0;
        }
        
        for (int i = 100000; i > 0; --i) {
            if (count[i] > 0) {
                long long take = min(total_k, count[i]);
                count[i] -= take;
                count[i - 1] += take;
                total_k -= take;
                if (total_k == 0) {
                    break;
                }
            }
        }
        
        long long ans = 0;
        for (int i = 0; i <= 100000; ++i) {
            if (count[i] > 0) {
                ans += count[i] * (long long)i * i;
            }
        }
        
        return ans;
    }
};