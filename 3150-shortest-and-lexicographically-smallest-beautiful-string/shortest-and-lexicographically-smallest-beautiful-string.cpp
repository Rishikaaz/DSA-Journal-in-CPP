class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int bestLeft = -1;
        int minLength = s.length() + 1;
        int ones = 0;
        
        for (int l = 0, r = 0; r < s.length(); ++r) {
            if (s[r] == '1') ++ones;
            
            while (ones == k) {
                int currentLength = r - l + 1;
                
                if (currentLength < minLength) {
                    bestLeft = l;
                    minLength = currentLength;
                } else if (currentLength == minLength) {
                    if (s.compare(l, minLength, s, bestLeft, minLength) < 0) {
                        bestLeft = l;
                    }
                }
                
                if (s[l++] == '1') --ones;
            }
        }
        
        return bestLeft == -1 ? "" : s.substr(bestLeft, minLength);
    }
};