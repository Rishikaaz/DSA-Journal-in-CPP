class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n < 3)
            return n;
        int len = __lg(n) + 1;
        return 1 << len;
    }
};