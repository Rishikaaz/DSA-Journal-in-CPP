class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], i};
        }
        sort(arr.begin(), arr.end());

        vector<vector<pair<int, int>>> groups;
        for (int i = 0; i < n; ++i) {
            if (groups.empty() || arr[i].first - groups.back().back().first > limit) {
                groups.push_back({arr[i]});
            } else {
                groups.back().push_back(arr[i]);
            }
        }

        vector<int> res(n);
        for (const auto& group : groups) {
            vector<int> indices;
            for (const auto& p : group) {
                indices.push_back(p.second);
            }
            sort(indices.begin(), indices.end());
            for (size_t i = 0; i < indices.size(); ++i) {
                res[indices[i]] = group[i].first;
            }
        }

        return res;
    }
};