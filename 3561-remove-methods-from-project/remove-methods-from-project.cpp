class Solution {
public:
    vector<int> remainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for (const auto& invocation : invocations) {
            graph[invocation[0]].push_back(invocation[1]);
        }
        queue<int> q;
        q.push(k);
        vector<bool> seen(n, false);
        seen[k] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
        for (int u = 0; u < n; ++u) {
            if (seen[u])
                continue;
            for (int v : graph[u]) {
                if (seen[v]) {
                    vector<int> ans(n);
                    iota(ans.begin(), ans.end(), 0);
                    return ans;
                }
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (!seen[i]) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};