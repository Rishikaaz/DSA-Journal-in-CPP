class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int totalxor = 0;
        bool hasnonzero = false;
        for (int num : nums) {
            totalxor ^= num;
            if (num != 0)
                hasnonzero = true;
        }
        if (!hasnonzero)
            return 0;
        if (totalxor != 0)
            return n;
        return n - 1;
    }
};