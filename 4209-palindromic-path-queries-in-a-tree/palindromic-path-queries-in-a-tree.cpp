class Solution {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos;
    vector<int> tree_mask;
    int cur_pos;
    string node_char;

    int dfs1(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        int size = 1, max_sub_size = 0;
        for (int v : adj[u]) {
            if (v != p) {
                int sub_size = dfs1(v, u, d + 1);
                size += sub_size;
                if (sub_size > max_sub_size) {
                    max_sub_size = sub_size;
                    heavy[u] = v;
                }
            }
        }
        return size;
    }

    void dfs2(int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) {
            dfs2(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) {
                dfs2(v, v);
            }
        }
    }

    void update_seg(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree_mask[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update_seg(2 * node, l, mid, idx, val);
        else update_seg(2 * node + 1, mid + 1, r, idx, val);
        tree_mask[node] = tree_mask[2 * node] ^ tree_mask[2 * node + 1];
    }

    int query_seg(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree_mask[node];
        int mid = (l + r) / 2;
        return query_seg(2 * node, l, mid, ql, qr) ^ query_seg(2 * node + 1, mid + 1, r, ql, qr);
    }

    int query_path(int u, int v) {
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            res ^= query_seg(1, 0, n - 1, pos[head[v]], pos[v]);
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res ^= query_seg(1, 0, n - 1, pos[u], pos[v]);
        return res;
    }

public:
    vector<bool> palindromePath(int n_nodes, vector<vector<int>>& edges, string s, vector<string>& queries) {
        n = n_nodes;
        node_char = s;
        adj.assign(n, vector<int>());
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        cur_pos = 0;

        dfs1(0, -1, 0);
        dfs2(0, 0);

        tree_mask.assign(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            update_seg(1, 0, n - 1, pos[i], 1 << (node_char[i] - 'a'));
        }

        vector<bool> answer;
        for (const string& q : queries) {
            if (q[0] == 'u') {
                int space1 = q.find(' ', 7);
                int u = stoi(q.substr(7, space1 - 7));
                char c = q.back();
                node_char[u] = c;
                update_seg(1, 0, n - 1, pos[u], 1 << (c - 'a'));
            } else {
                int space1 = q.find(' ', 6);
                int u = stoi(q.substr(6, space1 - 6));
                int v = stoi(q.substr(space1 + 1));
                int mask = query_path(u, v);
                answer.push_back(mask == 0 || (mask & (mask - 1)) == 0);
            }
        }
        return answer;
    }
};