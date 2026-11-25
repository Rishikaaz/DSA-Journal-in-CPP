class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const long long BASE = 1315423911LL;
        const long long MOD = 1000000007LL;

        vector<long long> powBase(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            powBase[i] = (powBase[i - 1] * BASE) % MOD;
        }

        auto hasUniqueOfLen = [&](int len) -> bool {
            if (len > n) return false;
            unordered_map<long long, int> freq;
            freq.reserve(n - len + 1);

            long long h = 0;
            for (int i = 0; i < len; i++) {
                h = (h * BASE + nums[i]) % MOD;
            }
            freq[h]++;

            for (int i = len; i < n; i++) {
                long long outVal = (nums[i - len] * powBase[len - 1]) % MOD;
                h = (h - outVal + MOD) % MOD;
                h = (h * BASE + nums[i]) % MOD;
                freq[h]++;
            }

            for (const auto& [_, count] : freq) {
                if (count == 1) return true;
            }
            return false;
        };

        int lo = 1, hi = n, ans = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUniqueOfLen(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};