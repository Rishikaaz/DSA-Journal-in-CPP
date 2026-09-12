class Solution {
    struct T {
        long long weight = 0;
        vector<int> selected;
        bool computed = false;
    };

    vector<vector<T>> memo;

    int findFirstGreater(const vector<tuple<int, int, int, int>>& intervals, int startFrom, int rightBoundary) {
        int l = startFrom;
        int r = intervals.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (get<0>(intervals[m]) > rightBoundary) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

    T solve(const vector<tuple<int, int, int, int>>& intervals, int i, int quota) {
        if (i == intervals.size() || quota == 0) return {0, {}, true};
        if (memo[i][quota].computed) return memo[i][quota];

        T skip = solve(intervals, i + 1, quota);

        auto [l, r, weight, originalIndex] = intervals[i];
        int j = findFirstGreater(intervals, i + 1, r);
        T nextRes = solve(intervals, j, quota - 1);

        vector<int> newSelected = nextRes.selected;
        newSelected.push_back(originalIndex);
        sort(newSelected.begin(), newSelected.end());

        T pick = {weight + nextRes.weight, newSelected, true};

        if (pick.weight > skip.weight || (pick.weight == skip.weight && pick.selected < skip.selected)) {
            memo[i][quota] = pick;
        } else {
            memo[i][quota] = skip;
        }
        memo[i][quota].computed = true;

        return memo[i][quota];
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& input) {
        int n = input.size();
        vector<tuple<int, int, int, int>> intervals;
        for (int i = 0; i < n; ++i) {
            intervals.emplace_back(input[i][0], input[i][1], input[i][2], i);
        }

        sort(intervals.begin(), intervals.end());

        memo.assign(n, vector<T>(5));

        return solve(intervals, 0, 4).selected;
    }
};