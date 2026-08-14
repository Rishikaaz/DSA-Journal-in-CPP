class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.length();
        int left = 0, maxlength = 0;
        unordered_map<char, int> chcnt;
        for (int right = 0; right < n; right++) {
            chcnt[s[right]]++;
            while (chcnt[s[right]] > 2) {
                chcnt[s[left]]--;
                left++;
            }
            maxlength = max(maxlength, right - left + 1);
        }
        return maxlength;
    }
};