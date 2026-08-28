class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }
        
        int key = -1;
        for (int c = 0; c < 26; ++c) {
            if (cnt[c] % 2 == 1) {
                if (n % 2 == 0 || key >= 0) {
                    return "";
                }
                key = c;
            }
        }
        
        vector<char> ans;
        
        auto check = [&](int c) {
            cnt[c] -= 2;
            ans.push_back('a' + c);
            
            string half = "";
            for (char ch : ans) {
                half += ch;
            }
            
            vector<int> temp_cnt = cnt;
            for (int d = 25; d >= 0; --d) {
                half.append(temp_cnt[d] / 2, 'a' + d);
            }
            
            string tmp = half;
            if (key >= 0) {
                tmp += string(1, 'a' + key);
            }
            string rev_half = half;
            reverse(rev_half.begin(), rev_half.end());
            tmp += rev_half;
            
            if (tmp > target) {
                return true;
            }
            
            cnt[c] += 2;
            ans.pop_back();
            return false;
        };
        
        for (int i = 0; i < n / 2; ++i) {
            bool matched = false;
            for (int c = 0; c < 26; ++c) {
                if (cnt[c] >= 2 && check(c)) {
                    matched = true;
                    break;
                }
            }
            if (!matched) {
                return "";
            }
        }
        
        string ret = "";
        for (char ch : ans) {
            ret += ch;
        }
        if (key >= 0) {
            ret += string(1, 'a' + key);
        }
        string rev_ans = string(ans.rbegin(), ans.rend());
        ret += rev_ans;
        
        return ret > target ? ret : "";
    }
};