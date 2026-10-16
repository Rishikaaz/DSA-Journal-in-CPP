class Solution {
    long long sum_sq[400005];
    long long sum_val[400005];
    long long lazy[400005];
    long long MOD = 1e9 + 7;

    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;
        sum_sq[node] = (sum_sq[node] + 2 * v * sum_val[node] + v * v * len) % MOD;
        sum_val[node] = (sum_val[node] + v * len) % MOD;
        lazy[node] = (lazy[node] + v) % MOD;
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = (l + r) / 2;
            apply(2 * node, l, mid, lazy[node]);
            apply(2 * node + 1, mid + 1, r, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long v) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, v);
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, v);
        update(2 * node + 1, mid + 1, r, ql, qr, v);
        sum_sq[node] = (sum_sq[2 * node] + sum_sq[2 * node + 1]) % MOD;
        sum_val[node] = (sum_val[2 * node] + sum_val[2 * node + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < 4 * n; ++i) {
            sum_sq[i] = 0;
            sum_val[i] = 0;
            lazy[i] = 0;
        }

        unordered_map<int, int> lastSeen;
        long long ans = 0;

        for (int r = 0; r < n; ++r) {
            int l = lastSeen.count(nums[r]) ? lastSeen[nums[r]] + 1 : 0;
            update(1, 0, n - 1, l, r, 1);
            lastSeen[nums[r]] = r;
            ans = (ans + sum_sq[1]) % MOD;
        }

        return ans;
    }
};