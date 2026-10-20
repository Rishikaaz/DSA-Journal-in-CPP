class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> pref_max(n);
        int curr_max = -1;
        for (int i = 0; i < n; ++i) {
            curr_max = max(curr_max, nums[i]);
            pref_max[i] = curr_max;
        }
        
        vector<int> suff_min(n);
        int curr_min = INT_MAX;
        for (int i = n - 1; i >= 0; --i) {
            curr_min = min(curr_min, nums[i]);
            suff_min[i] = curr_min;
        }
        
        long long total_sum = 0;
        
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;
            
            bool valid = true;
            for (int i = k - 1; i < n - 1; i += k) {
                if (pref_max[i] > suff_min[i + 1]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
            
            for (int i = 0; i < n; i += k) {
                int drops = 0;
                for (int j = 0; j < k; ++j) {
                    if (nums[i + j] > nums[i + (j + 1) % k]) {
                        drops++;
                    }
                }
                if (drops > 1) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                total_sum += k;
            }
        }
        
        return total_sum;
    }
};