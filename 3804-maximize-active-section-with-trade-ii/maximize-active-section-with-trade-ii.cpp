struct Group {
    int start;
    int length;
};
class SparseTable {
    int n;
    vector<vector<int>> st;
public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;
        int max_log = 32 - __builtin_clz(n);
        st.assign(max_log, vector<int>(n));
        for (int j = 0; j < n; ++j) {
            st[0][j] = nums[j];
        }
        for (int i = 1; i < max_log; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int query(int l, int r) const {
        if (l > r || n == 0) return 0;
        int i = 31 - __builtin_clz(r - l + 1);
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }
};
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex;
        zeroGroupIndex.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
            }
            zeroGroupIndex.push_back(zeroGroups.empty() ? -1 : (int)zeroGroups.size() - 1);
        }
        if (zeroGroups.empty()) {
            return vector<int>(queries.size(), totalOnes);
        }
        vector<int> zeroMergeLengths;
        for (size_t i = 0; i + 1 < zeroGroups.size(); ++i) {
            zeroMergeLengths.push_back(zeroGroups[i].length + zeroGroups[i + 1].length);
        }
        SparseTable st(zeroMergeLengths);
        vector<int> ans;
        ans.reserve(queries.size());
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int left = (s[l] == '0') ? zeroGroups[zeroGroupIndex[l]].length - (l - zeroGroups[zeroGroupIndex[l]].start) : 0;
            int right = (s[r] == '0' && zeroGroupIndex[r] != -1) ? (r - zeroGroups[zeroGroupIndex[r]].start + 1) : 0;
            int startAdjacentGroupIndex = zeroGroupIndex[l] + 1;
            int endAdjacentGroupIndex = (s[r] == '1' ? zeroGroupIndex[r] : zeroGroupIndex[r] - 1) - 1;
            int activeSections = totalOnes;
            if (s[l] == '0' && s[r] == '0' && zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                activeSections = max(activeSections, totalOnes + left + right);
            } 
            else if (startAdjacentGroupIndex <= endAdjacentGroupIndex) {
                activeSections = max(activeSections, totalOnes + st.query(startAdjacentGroupIndex, endAdjacentGroupIndex));
            }
            if (s[l] == '0' && zeroGroupIndex[l] + 1 <= (s[r] == '1' ? zeroGroupIndex[r] : zeroGroupIndex[r] - 1)) {
                activeSections = max(activeSections, totalOnes + left + zeroGroups[zeroGroupIndex[l] + 1].length);
            }
            if (s[r] == '0' && zeroGroupIndex[l] < zeroGroupIndex[r] - 1) {
                activeSections = max(activeSections, totalOnes + right + zeroGroups[zeroGroupIndex[r] - 1].length);
            }
            ans.push_back(activeSections);
        }
        return ans;
    }
};