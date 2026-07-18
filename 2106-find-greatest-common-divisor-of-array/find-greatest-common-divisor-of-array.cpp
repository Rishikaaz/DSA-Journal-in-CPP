class Solution {
private:
    int getgcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

public:
    int findGCD(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int gcd = getgcd(nums[0], nums[n - 1]);
        return gcd;
    }
};