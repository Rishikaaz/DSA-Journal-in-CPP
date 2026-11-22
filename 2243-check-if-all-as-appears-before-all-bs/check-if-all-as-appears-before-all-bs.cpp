class Solution {
public:
    bool checkString(string s) {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'a') {
                continue;
            } else if (s[i] == 'b') {
                if (s[i + 1] == 'b') {
                    continue;
                } else if (s[i + 1] == 'a') {
                    return false;
                    break;
                }
            }
        }
        return true;
    }
};