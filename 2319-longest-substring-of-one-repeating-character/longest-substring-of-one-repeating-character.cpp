class Solution {
    struct Node {
        int l_len, r_len, max_len;
        char l_char, r_char;
    };

    vector<Node> tree;
    string s;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {1, 1, 1, s[l], s[l]};
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        update_node(node, 2 * node, 2 * node + 1, l, mid, r);
    }

    void update_node(int node, int left_child, int right_child, int l, int mid,
                     int r) {
        auto& lc = tree[left_child];
        auto& rc = tree[right_child];

        int l_len = lc.l_len;
        if (lc.l_len == (mid - l + 1) && lc.l_char == rc.l_char) {
            l_len += rc.l_len;
        }

        int r_len = rc.r_len;
        if (rc.r_len == (r - mid) && rc.r_char == lc.r_char) {
            r_len += lc.r_len;
        }

        int max_len = max({lc.max_len, rc.max_len,
                           (lc.r_char == rc.l_char ? lc.r_len + rc.l_len : 0)});

        tree[node] = {l_len, r_len, max_len, lc.l_char, rc.r_char};
    }

    void update(int node, int l, int r, int idx, char ch) {
        if (l == r) {
            s[idx] = ch;
            tree[node] = {1, 1, 1, ch, ch};
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, r, idx, ch);
        }
        update_node(node, 2 * node, 2 * node + 1, l, mid, r);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;
        int n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> ans;
        int k = queryCharacters.length();
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].max_len);
        }
        return ans;
    }
};