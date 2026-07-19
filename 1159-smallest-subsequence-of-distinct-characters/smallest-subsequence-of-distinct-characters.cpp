class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIdx(26, 0);
        for (int i = 0; i < s.length(); i++) {
            lastIdx[s[i] - 'a'] = i;
        }
        vector<bool> seen(26, false);
        string result = "";
        for (int i = 0; i < s.length(); i++) {
            char curr = s[i];
            if (seen[curr - 'a'])
                continue;
            while (!result.empty() && result.back() > curr &&
                   lastIdx[result.back() - 'a'] > i) {
                seen[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(curr);
            seen[curr - 'a'] = true;
        }
        return result;
    }
};