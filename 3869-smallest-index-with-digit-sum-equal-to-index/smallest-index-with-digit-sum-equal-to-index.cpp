class Solution {
private:
    int digitsum(int n) {
        int sum = 0;
        if (n < 10)
            return n;
        else {
            while (n > 0) {
                int fd = 0;
                fd = n % 10;
                sum += fd;
                n /= 10;
            }
            return sum;
        }
    }

public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int sum = digitsum(nums[i]);
            if (i == sum) {
                return i;
            }
        }
        return -1;
    }
};