class Solution {
    void bfs(int sr, int sc, int R, int C, vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        q.push({sr, sc});
        grid[sr][sc] = 1;
        
        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int R = grid.size();
        int C = grid[0].size();
        
        // 1. Flood-fill all 0s connected to the boundary
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if ((r == 0 || r == R - 1 || c == 0 || c == C - 1) && grid[r][c] == 0) {
                    bfs(r, c, R, C, grid);
                }
            }
        }
        
        // 2. Count remaining closed islands
        int count = 0;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == 0) {
                    count++;
                    bfs(r, c, R, C, grid);
                }
            }
        }
        
        return count;
    }
};