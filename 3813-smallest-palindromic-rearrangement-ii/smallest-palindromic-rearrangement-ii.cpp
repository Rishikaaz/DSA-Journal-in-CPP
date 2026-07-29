class Solution {
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        long long res = 1;
        for (int i = 1; i <= min(r, n - r); ++i) {
            res = res * (n - i + 1) / i;
            if (res > 1e6) return 1e6 + 1;
        }
        return res;
    }
    long long countPerms(vector<int> cnt) {
        long long res = 1, rem = accumulate(cnt.begin(), cnt.end(), 0);
        for (int c : cnt) {
            res *= nCr(rem, c);
            if (res > 1e6) return 1e6 + 1;
            rem -= c;
        }
        return res;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        string left = "", mid = "";
        vector<int> half(26, 0);
        for (int i = 0; i < 26; ++i) {
            half[i] = cnt[i] / 2;
            if (cnt[i] % 2) mid = string(1, 'a' + i);
        }
        if (countPerms(half) < k) return "";
        int len = accumulate(half.begin(), half.end(), 0);
        for (int pos = 0; pos < len; ++pos) {
            for (int i = 0; i < 26; ++i) {
                if (!half[i]) continue;
                half[i]--;
                long long ways = countPerms(half);
                if (ways >= k) { left += ('a' + i); break; }
                k -= ways;
                half[i]++;
            }
        }
        string right = left;
        reverse(right.begin(), right.end());
        return left + mid + right;
    }
};