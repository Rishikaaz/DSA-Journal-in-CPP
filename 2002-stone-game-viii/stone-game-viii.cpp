class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix(n);
        prefix[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] + stones[i];
        }
        int max_diff = prefix[n - 1];
        for (int i = n - 3; i >= 0; --i) {
            max_diff = max(max_diff, prefix[i + 1] - max_diff);
        }
        return max_diff;
    }
};