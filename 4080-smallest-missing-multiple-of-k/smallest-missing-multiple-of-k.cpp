class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_set<int> numb(nums.begin(), nums.end());
        for (int i = 1;; i++) {
            int x = i * k;
            if (numb.find(x) == numb.end()) {
                return x;
            }
        }
    }
};