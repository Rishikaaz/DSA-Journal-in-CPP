class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;
        k %= total;
        if (k == 0) return grid;
        while (k > 0) {
            vector<vector<int>> res(m, vector<int>(n));
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    int next_i = i;
                    int next_j = j + 1;
                    if (next_j == n) {
                        next_j = 0;
                        next_i = (i + 1) % m; 
                    }
                    res[next_i][next_j] = grid[i][j];
                }
            }
            grid = res;
            k--;
        } 
        return grid;
    }
};