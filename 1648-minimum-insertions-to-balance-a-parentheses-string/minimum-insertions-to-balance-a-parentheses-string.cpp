class Solution {
public:
    int minInsertions(string s) {
        int open_brackets = 0;
        int ans = 0;
        int n = s.length();
        int i = 0;
        
        while (i < n) {
            if (s[i] == '(') {
                open_brackets++;
                i++;
            } else {
                if (i + 1 < n && s[i + 1] == ')') {
                    i += 2;
                } else {
                    ans++;
                    i++;
                }
                
                if (open_brackets > 0) {
                    open_brackets--;
                } else {
                    ans++;
                }
            }
        }
        
        return ans + open_brackets * 2;
    }
};