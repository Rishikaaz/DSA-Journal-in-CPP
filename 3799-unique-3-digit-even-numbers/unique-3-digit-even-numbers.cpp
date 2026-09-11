class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        unordered_set<int> unique_nums;
        int n = digits.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (i != j && j != k && i != k) {
                        int a = digits[i];
                        int b = digits[j];
                        int c = digits[k];
                        if (a != 0 && c % 2 == 0) {
                            unique_nums.insert(a * 100 + b * 10 + c);
                        }
                    }
                }
            }
        }
        
        return unique_nums.size();
    }
};