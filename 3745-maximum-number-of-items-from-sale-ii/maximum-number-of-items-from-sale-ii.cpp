class Solution {
private:
    struct Deal {
        long long gain;
        long long cost;
        long long maxCnt;
    };

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = static_cast<int>(items.size());
        vector<long long> cntFactor(n + 1, 0);
        for (const auto& it : items) {
            cntFactor[it[0]]++;
        }

        vector<long long> multSum(n + 1, 0);
        for (int f = 1; f <= n; f++) {
            for (int m = f; m <= n; m += f) {
                multSum[f] += cntFactor[m];
            }
        }

        vector<Deal> deals;
        deals.reserve(2 * n);
        const long long INF = 4e18;

        for (int i = 0; i < n; i++) {
            long long f = items[i][0];
            long long p = items[i][1];
            long long b = max(0LL, multSum[f] - 1);

            if (b > 0) {
                deals.push_back({2, p, b});
            }
            deals.push_back({1, p, INF});
        }

        sort(deals.begin(), deals.end(), [](const Deal& a, const Deal& b) {
            return a.gain * b.cost > b.gain * a.cost;
        });

        long long remBudget = budget;
        long long totalItems = 0;

        for (const auto& d : deals) {
            if (remBudget < d.cost) continue;
            long long take = min(d.maxCnt, remBudget / d.cost);
            totalItems += take * d.gain;
            remBudget -= take * d.cost;
        }

        return static_cast<int>(totalItems);
    }
};