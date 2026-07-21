class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int res = 0;
        for (char c : s) {
            if (c == '1') res++;
        }
        string t = "1" + s + "1";
        vector<pair<char, int>> r;
        int n = t.length(), i = 0;
        while (i < n) {
            int j = i;
            while (j < n && t[j] == t[i]) j++;
            r.push_back({t[i], j - i});
            i = j;
        }
        int g = 0;
        for (int k = 1; k < (int)r.size() - 1; k++) {
            if (r[k].first == '1') {
                g = max(g, r[k - 1].second + r[k + 1].second);
            }
        }

        return res + g;
    }
};