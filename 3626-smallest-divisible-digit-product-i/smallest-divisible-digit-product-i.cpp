class Solution {
public:
    int smallestNumber(int n, int t) {
        for (int i = n;; i++) {
            int temp = i;
            int product = 1;
            bool hasZero = false;
            while (temp > 0) {
                int digit = temp % 10;
                if (digit == 0) {
                    hasZero = true;
                    break;
                }
                product *= digit;
                temp /= 10;
            }
            if (hasZero) {
                return i;
            }
            if (product % t == 0) {
                return i;
            }
        }
    }
};