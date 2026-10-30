class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> g(n);
        for (const auto& edge : edges) {
            g[edge[0]].push_back({edge[1], edge[2]});
        }
        
        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));
        dist[0][1] = 0;
        
        priority_queue<tuple<int, int, int>, 
                       vector<tuple<int, int, int>>, 
                       greater<tuple<int, int, int>>> pq;
        pq.push({0, 0, 1});
        
        while (!pq.empty()) {
            auto [d, u, cur] = pq.top();
            pq.pop();
            
            if (u == n - 1) return d;
            if (d > dist[u][cur]) continue;
            
            for (auto& edge : g[u]) {
                int v = edge.first;
                int w = edge.second;
                int nxt = (labels[v] != labels[u]) ? 1 : cur + 1;
                int nd = d + w;
                
                if (nxt <= k && nd < dist[v][nxt]) {
                    dist[v][nxt] = nd;
                    pq.push({nd, v, nxt});
                }
            }
        }
        
        return -1;
    }
};