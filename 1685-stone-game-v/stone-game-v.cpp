#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }

        vector<vector<int>> memo(n, vector<int>(n, -1));

        auto getSum = [&](int i, int j) {
            return prefixSum[j + 1] - prefixSum[i];
        };

        function<int(int, int)> dfs = [&](int i, int j) {
            if (i == j)
                return 0;
            if (memo[i][j] != -1)
                return memo[i][j];

            int maxScore = 0;
            for (int k = i; k < j; ++k) {
                int leftSum = getSum(i, k);
                int rightSum = getSum(k + 1, j);

                if (leftSum < rightSum) {
                    maxScore = max(maxScore, leftSum + dfs(i, k));
                } else if (leftSum > rightSum) {
                    maxScore = max(maxScore, rightSum + dfs(k + 1, j));
                } else {
                    maxScore =
                        max(maxScore, leftSum + max(dfs(i, k), dfs(k + 1, j)));
                }
            }
            return memo[i][j] = maxScore;
        };

        return dfs(0, n - 1);
    }
};