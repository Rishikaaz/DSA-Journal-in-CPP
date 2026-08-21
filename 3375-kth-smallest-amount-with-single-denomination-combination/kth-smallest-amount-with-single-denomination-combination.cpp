class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        long long min_coin = *min_element(coins.begin(), coins.end());
        long long low = 1;
        long long high = min_coin * k;
        long long ans = high;
        int n = coins.size();
        auto count = [&](long long x) {
            long long total = 0;
            for (int mask = 1; mask < (1 << n); ++mask) {
                long long lcm_val = 1;
                int bits = 0;
                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1) {
                        bits++;
                        long long g = std::gcd(lcm_val, (long long)coins[i]);
                        if (lcm_val / g > x / coins[i]) {
                            lcm_val = x + 1;
                            break;
                        }
                        lcm_val = (lcm_val / g) * coins[i];
                        if (lcm_val > x) {
                            break;
                        }
                    }
                }
                if (lcm_val <= x) {
                    if (bits % 2 == 1) {
                        total += x / lcm_val;
                    } else {
                        total -= x / lcm_val;
                    }
                }
            }
            return total;
        };
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (count(mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};