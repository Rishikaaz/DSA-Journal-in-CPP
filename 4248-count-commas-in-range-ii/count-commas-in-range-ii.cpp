class Solution {
public:
    long long countCommas(long long n) {
        long long totalCommas = 0;
        long long powerOf10 = 1000;
        
        for (int k = 1; powerOf10 <= n; ++k) {
            long long nextPower = powerOf10 * 1000;
            long long upperBound = (n < nextPower - 1) ? n : nextPower - 1;
            long long count = upperBound - powerOf10 + 1;
            
            if (count > 0) {
                totalCommas += count * k;
            }
            powerOf10 = nextPower;
        }
        
        return totalCommas;
    }
};