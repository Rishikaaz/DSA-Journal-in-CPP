class Solution {
public:
    int minOperations(string s) {
        int n = s.length();
        if (is_sorted(s.begin(), s.end())) return 0;
        if (n == 2) return -1;
        
        int min_c = 0, max_c = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] < s[min_c]) min_c = i;
            if (s[i] >= s[max_c]) max_c = i;
        }
        
        if (min_c == 0 || max_c == n - 1) return 1;
        if (min_c == n - 1 && max_c == 0) return 3;
        return 2;
    }
};