class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();
        string ans = "";
        for (int i = 0; i < n; i++) {
            for (int j = i + k; j <= n; j++) {
                string t = s.substr(i, j - i);
                int ones = 0;
                for (char c : t) {
                    if (c == '1')
                        ones++;
                }
                if (ones == k) {
                    if (ans == "" || (t.length() < ans.length()) ||
                        (t.length() == ans.length() && t < ans)) {
                        ans = t;
                    }
                }
            }
        }
        return ans;
    }
};