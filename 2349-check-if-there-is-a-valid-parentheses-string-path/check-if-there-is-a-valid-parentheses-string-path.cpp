using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        if ((m + n) % 2 == 0) return false;
        
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;
        
        int max_open = (m + n) / 2;
        
        vector<vector<vector<bool>>> dp(m, vector<vector<bool>>(n, vector<bool>(max_open + 1, false)));
        
        dp[0][0][1] = true;
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) continue;
                
                int val = (grid[r][c] == '(' ? 1 : -1);
                
                for (int b = 0; b <= max_open; ++b) {
                    int prev_b = b - val;
                    if (prev_b >= 0 && prev_b <= max_open) {
                        bool from_top = (r > 0 && dp[r - 1][c][prev_b]);
                        bool from_left = (c > 0 && dp[r][c - 1][prev_b]);
                        
                        if (from_top || from_left) {
                            dp[r][c][b] = true;
                        }
                    }
                }
            }
        }
        
        return dp[m - 1][n - 1][0];
    }
};