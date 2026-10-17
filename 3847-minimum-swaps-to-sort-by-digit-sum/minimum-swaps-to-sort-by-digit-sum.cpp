class Solution {
    int getDigitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> target(n);
        for (int i = 0; i < n; ++i) {
            target[i] = {getDigitSum(nums[i]), nums[i]};
        }
        
        sort(target.begin(), target.end());
        
        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) {
            pos[target[i].second] = i;
        }
        
        vector<bool> vis(n, false);
        int swaps = 0;
        
        for (int i = 0; i < n; ++i) {
            if (!vis[i] && pos[nums[i]] != i) {
                int cycle_size = 0;
                int j = i;
                while (!vis[j]) {
                    vis[j] = true;
                    j = pos[nums[j]];
                    cycle_size++;
                }
                swaps += (cycle_size - 1);
            }
        }
        
        return swaps;
    }
};