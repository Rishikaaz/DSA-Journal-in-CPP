class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long rem = t;
        int c7 = 0, c5 = 0, c3 = 0, c2 = 0;
        
        while (rem % 7 == 0) { c7++; rem /= 7; }
        while (rem % 5 == 0) { c5++; rem /= 5; }
        while (rem % 3 == 0) { c3++; rem /= 3; }
        while (rem % 2 == 0) { c2++; rem /= 2; }
        
        if (rem > 1) return "-1";
        
        int n = num.length();
        
        auto get_min_digits = [&](int r2, int r3, int r5, int r7) {
            string s = "";
            while (r7 > 0) { s += '7'; r7--; }
            while (r3 >= 2) { s += '9'; r3 -= 2; }
            while (r2 >= 3) { s += '8'; r2 -= 3; }
            while (r2 >= 1 && r3 >= 1) { s += '6'; r2 -= 1; r3 -= 1; }
            while (r5 > 0) { s += '5'; r5--; }
            while (r2 >= 2) { s += '4'; r2 -= 2; }
            while (r3 > 0) { s += '3'; r3--; }
            while (r2 > 0) { s += '2'; r2--; }
            sort(s.begin(), s.end());
            return s;
        };

        string min_req_str = get_min_digits(c2, c3, c5, c7);
        if (min_req_str.length() > n) {
            return min_req_str;
        }

        // Find the first zero if any
        int zero_idx = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                zero_idx = i;
                break;
            }
        }

        if (zero_idx != -1) {
            string prefix = num.substr(0, zero_idx);
            long long p2 = 0, p3 = 0, p5 = 0, p7 = 0;
            for (char c : prefix) {
                int d = c - '0';
                while (d % 7 == 0) { p7++; d /= 7; }
                while (d % 5 == 0) { p5++; d /= 5; }
                while (d % 3 == 0) { p3++; d /= 3; }
                while (d % 2 == 0) { p2++; d /= 2; }
            }
            int rem2 = max(0, c2 - (int)p2);
            int rem3 = max(0, c3 - (int)p3);
            int rem5 = max(0, c5 - (int)p5);
            int rem7 = max(0, c7 - (int)p7);
            
            string suffix = get_min_digits(rem2, rem3, rem5, rem7);
            if (prefix.length() + suffix.length() <= n) {
                string res = prefix;
                while (res.length() + suffix.length() < n) {
                    res += '1';
                }
                return res + suffix;
            }
        }

        // Check if current num is already valid
        {
            long long p2 = 0, p3 = 0, p5 = 0, p7 = 0;
            bool has_zero = false;
            for (char c : num) {
                if (c == '0') has_zero = true;
                int d = c - '0';
                if (d > 0) {
                    while (d % 7 == 0) { p7++; d /= 7; }
                    while (d % 5 == 0) { p5++; d /= 5; }
                    while (d % 3 == 0) { p3++; d /= 3; }
                    while (d % 2 == 0) { p2++; d /= 2; }
                }
            }
            if (!has_zero && p2 >= c2 && p3 >= c3 && p5 >= c5 && p7 >= c7) {
                return num;
            }
        }

        // Backtrack from right to left to find the smallest valid greater number
        long long cur2 = 0, cur3 = 0, cur5 = 0, cur7 = 0;
        for (char c : num) {
            int d = c - '0';
            if (d == 0) continue;
            while (d % 7 == 0) { cur7++; d /= 7; }
            while (d % 5 == 0) { cur5++; d /= 5; }
            while (d % 3 == 0) { cur3++; d /= 3; }
            while (d % 2 == 0) { cur2++; d /= 2; }
        }

        for (int i = n - 1; i >= 0; --i) {
            int d_curr = num[i] - '0';
            if (d_curr > 0) {
                long long d2 = 0, d3 = 0, d5 = 0, d7 = 0;
                int tmp = d_curr;
                while (tmp % 7 == 0) { d7++; tmp /= 7; }
                while (tmp % 5 == 0) { d5++; tmp /= 5; }
                while (tmp % 3 == 0) { d3++; tmp /= 3; }
                while (tmp % 2 == 0) { d2++; tmp /= 2; }
                cur2 -= d2; cur3 -= d3; cur5 -= d5; cur7 -= d7;
            }

            for (int d_val = max(1, d_curr + 1); d_val <= 9; ++d_val) {
                char d_char = '0' + d_val;
                long long nd2 = 0, nd3 = 0, nd5 = 0, nd7 = 0;
                int ntmp = d_val;
                while (ntmp % 7 == 0) { nd7++; ntmp /= 7; }
                while (ntmp % 5 == 0) { nd5++; ntmp /= 5; }
                while (ntmp % 3 == 0) { nd3++; ntmp /= 3; }
                while (ntmp % 2 == 0) { nd2++; ntmp /= 2; }

                int rem2 = max(0LL, c2 - (cur2 + nd2));
                int rem3 = max(0LL, c3 - (cur3 + nd3));
                int rem5 = max(0LL, c5 - (cur5 + nd5));
                int rem7 = max(0LL, c7 - (cur7 + nd7));

                string suffix = get_min_digits(rem2, rem3, rem5, rem7);
                string candidate = num.substr(0, i) + d_char;
                if (candidate.length() + suffix.length() <= n) {
                    while (candidate.length() + suffix.length() < n) {
                        candidate += '1';
                    }
                    return candidate + suffix;
                }
            }
        }

        // Fallback: If no valid number of length n exists, construct one of length n + 1
        int target_len = max(n + 1, (int)min_req_str.length());
        string res = "";
        while (res.length() + min_req_str.length() < target_len) {
            res += '1';
        }
        return res + min_req_str;
    }
};