class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<int> ans(m);
        
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        vector<pair<int, int>> indexed_queries(m);
        for (int i = 0; i < m; ++i) {
            indexed_queries[i] = {queries[i], i};
        }
        sort(indexed_queries.begin(), indexed_queries.end());
        
        int log_idx_left = 0, log_idx_right = 0;
        int num_logs = logs.size();
        vector<int> server_counts(n + 1, 0);
        int active_servers = 0;
        
        for (auto& [q, orig_idx] : indexed_queries) {
            int window_start = q - x;
            int window_end = q;
            
            while (log_idx_right < num_logs && logs[log_idx_right][1] <= window_end) {
                int server = logs[log_idx_right][0];
                if (server_counts[server] == 0) {
                    active_servers++;
                }
                server_counts[server]++;
                log_idx_right++;
            }
            
            while (log_idx_left < num_logs && logs[log_idx_left][1] < window_start) {
                int server = logs[log_idx_left][0];
                server_counts[server]--;
                if (server_counts[server] == 0) {
                    active_servers--;
                }
                log_idx_left++;
            }
            
            ans[orig_idx] = n - active_servers;
        }
        
        return ans;
    }
};