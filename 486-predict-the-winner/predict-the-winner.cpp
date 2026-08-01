class Solution {
private:
    int memo[20][20];
    int solve(vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }
        if (memo[left][right] != -1) {
            return memo[left][right];
        }
        int pickLeft = nums[left] - solve(nums, left + 1, right);
        int pickRight = nums[right] - solve(nums, left, right - 1);
        return memo[left][right] = max(pickLeft, pickRight);
    }

public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        memset(memo, -1, sizeof(memo));
        return solve(nums, 0, n - 1) >= 0;
    }
};