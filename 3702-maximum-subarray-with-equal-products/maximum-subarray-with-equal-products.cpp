class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long lcm_num = 1;
            long long gcd_num = 0;
            for (int j = i; j < n; j++) {
                long long x = nums[j];
                prod *= x;
                if (prod > 25200) {
                    break;
                }
                lcm_num = lcm(lcm_num, x);
                gcd_num = gcd(gcd_num, x);
                long long product = lcm_num * gcd_num;
                if (prod == product) {
                    cnt = max(cnt, j - i + 1);
                }
            }
        }
        return cnt;
    }
};