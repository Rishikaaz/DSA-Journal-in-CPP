class Solution {
    struct Node {
        int prod;
        int count[5];
    };

    int k_val;
    vector<Node> tree;
    vector<int> arr;

    Node combine(const Node& left, const Node& right) {
        Node res;
        res.prod = (left.prod * right.prod) % k_val;
        for (int i = 0; i < k_val; ++i) {
            res.count[i] = left.count[i];
        }
        for (int i = 0; i < k_val; ++i) {
            int rem = (i * left.prod) % k_val;
            res.count[rem] += right.count[i];
        }
        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node].prod = arr[start] % k_val;
            for (int i = 0; i < k_val; ++i) {
                tree[node].count[i] = 0;
            }
            tree[node].count[tree[node].prod] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            arr[idx] = val;
            tree[node].prod = val % k_val;
            for (int i = 0; i < k_val; ++i) {
                tree[node].count[i] = 0;
            }
            tree[node].count[tree[node].prod] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }

    Node query_tree(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            Node identity;
            identity.prod = 1;
            for (int i = 0; i < k_val; ++i) {
                identity.count[i] = 0;
            }
            return identity;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        Node left_res = query_tree(2 * node, start, mid, l, r);
        Node right_res = query_tree(2 * node + 1, mid + 1, end, l, r);
        if (r < start || l > mid && r >= start && l <= end) {
        }
        bool left_in = !(r < start || mid < l);
        bool right_in = !(r < mid + 1 || end < l);
        if (!left_in) return right_res;
        if (!right_in) return left_res;
        return combine(left_res, right_res);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        k_val = k;
        arr = nums;
        tree.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> result;
        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];

            if (arr[idx] != val) {
                update(1, 0, n - 1, idx, val);
            }

            if (start >= n) {
                result.push_back(0);
                continue;
            }

            Node res = query_tree(1, 0, n - 1, start, n - 1);
            result.push_back(res.count[x]);
        }

        return result;
    }
};