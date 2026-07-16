class Solution {
private:
    int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        int mx = 0;
        vector<int> prefixgcd(n);
        for (int i = 0; i < nums.size(); i++) {
            mx = max(mx, nums[i]);
            prefixgcd[i] = gcd(nums[i], mx);
        }
        sort(prefixgcd.begin(), prefixgcd.end());
        int l = 0, r = prefixgcd.size() - 1;
        long long totalsum = 0;
        while (l < r) {
            totalsum += gcd(prefixgcd[l], prefixgcd[r]);
            l++;
            r--;
        }
        return totalsum;
    }
};