class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        const int n = s.length();
        vector<int> leftmost(26, n);
        vector<int> rightmost(26, -1);
        
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            leftmost[c] = min(leftmost[c], i);
            rightmost[c] = max(rightmost[c], i);
        }
        
        auto getNewRight = [&](int i) {
            int right = rightmost[s[i] - 'a'];
            for (int j = i; j <= right; ++j) {
                int c = s[j] - 'a';
                if (leftmost[c] < i) {
                    return -1;
                }
                right = max(right, rightmost[c]);
            }
            return right;
        };
        
        vector<string> ans;
        int right = -1;
        
        for (int i = 0; i < n; ++i) {
            if (i == leftmost[s[i] - 'a']) {
                int newRight = getNewRight(i);
                if (newRight == -1) continue;
                
                if (i <= right && !ans.empty()) {
                    ans.back() = s.substr(i, newRight - i + 1);
                } else {
                    ans.push_back(s.substr(i, newRight - i + 1));
                }
                right = newRight;
            }
        }
        
        return ans;
    }
};