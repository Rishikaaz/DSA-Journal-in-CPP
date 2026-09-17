class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> min_len(n, INT_MAX);
        unordered_map<int, int> prefix_sum_map;
        prefix_sum_map[0] = -1;
        
        int current_sum = 0;
        int ans = INT_MAX;
        int min_so_far = INT_MAX;
        
        for (int i = 0; i < n; ++i) {
            current_sum += arr[i];
            int needed_sum = current_sum - target;
            
            if (prefix_sum_map.find(needed_sum) != prefix_sum_map.end()) {
                int left = prefix_sum_map[needed_sum] + 1;
                int right = i;
                int len = right - left + 1;
                
                if (left > 0 && min_len[left - 1] != INT_MAX) {
                    ans = min(ans, min_len[left - 1] + len);
                }
                
                min_so_far = min(min_so_far, len);
            }
            
            min_len[i] = min_so_far;
            prefix_sum_map[current_sum] = i;
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};