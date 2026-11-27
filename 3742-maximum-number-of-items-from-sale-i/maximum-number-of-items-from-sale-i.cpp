class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = static_cast<int>(items.size());
        vector<int> bonus(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    bonus[i]++;
                }
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int cost = items[i][1];
            if (cost > budget) continue;

            // 1. At most one first-copy bonus for item i (backward loop = 0/1 choice)
            int firstVal = 1 + bonus[i];
            for (int b = budget; b >= cost; b--) {
                dp[b] = max(dp[b], dp[b - cost] + firstVal);
            }

            // 2. Additional copies of item i give 1 item each (forward loop = unbounded)
            for (int b = cost; b <= budget; b++) {
                dp[b] = max(dp[b], dp[b - cost] + 1);
            }
        }

        return dp[budget];
    }
};