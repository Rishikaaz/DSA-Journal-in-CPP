class Solution {
    int n;
    string targetStr;
    int count[26];
    string ans;

    bool dfs(int idx, bool is_greater, string& current) {
        if (idx == n) {
            if (is_greater) {
                ans = current;
                return true;
            }
            return false;
        }

        for (int i = 0; i < 26; ++i) {
            if (count[i] == 0) continue;

            char ch = 'a' + i;

            if (!is_greater && ch < targetStr[idx]) continue;

            bool next_is_greater = is_greater || (ch > targetStr[idx]);

            count[i]--;
            current.push_back(ch);

            if (dfs(idx + 1, next_is_greater, current)) {
                return true;
            }

            current.pop_back();
            count[i]++;
        }

        return false;
    }

public:
    string lexGreaterPermutation(string s, string target) {
        n = s.length();
        targetStr = target;
        fill(count, count + 26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string current = "";
        if (dfs(0, false, current)) {
            return ans;
        }
        return "";
    }
};