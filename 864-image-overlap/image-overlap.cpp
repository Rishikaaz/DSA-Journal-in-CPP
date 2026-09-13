class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> list1, list2;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1)
                    list1.push_back({r, c});
                if (img2[r][c] == 1)
                    list2.push_back({r, c});
            }
        }
        unordered_map<int, int> counts;
        int bestOverlap = 0;
        for (auto& p1 : list1) {
            for (auto& p2 : list2) {
                int rowDiff = p1.first - p2.first;
                int colDiff = p1.second - p2.second;
                int shiftKey = rowDiff * 100 + colDiff;
                counts[shiftKey]++;
                bestOverlap = max(bestOverlap, counts[shiftKey]);
            }
        }
        return bestOverlap;
    }
};