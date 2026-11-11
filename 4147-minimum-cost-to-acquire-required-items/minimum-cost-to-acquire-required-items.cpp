class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long n1 = need1;
        long long n2 = need2;
        
        auto get_cost = [&](long long x) {
            if (x < 0) x = 0;
            if (x > max(n1, n2)) x = max(n1, n2);
            long long c3 = x * costBoth;
            long long c1 = max(0LL, n1 - x) * cost1;
            long long c2 = max(0LL, n2 - x) * cost2;
            return c3 + c1 + c2;
        };
        
        vector<long long> candidates = {0, n1, n2, min(n1, n2), max(n1, n2)};
        long long min_c = -1;
        for (long long x : candidates) {
            if (x >= 0 && x <= max(n1, n2)) {
                long long c = get_cost(x);
                if (min_c == -1 || c < min_c) {
                    min_c = c;
                }
            }
        }
        
        long long low = 0, high = max(n1, n2);
        while (high - low > 2) {
            long long m1 = low + (high - low) / 3;
            long long m2 = high - (high - low) / 3;
            if (get_cost(m1) < get_cost(m2)) {
                high = m2;
            } else {
                low = m1;
            }
        }
        
        for (long long x = low; x <= high; ++x) {
            long long c = get_cost(x);
            if (min_c == -1 || c < min_c) {
                min_c = c;
            }
        }
        
        return min_c;
    }
};