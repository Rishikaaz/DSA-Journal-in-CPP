class Solution {
public:
    int minMoves(vector<string>& classroom, int max_energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = 0, start_c = 0;
        int litter_cnt = 0;
        int litter_map[20][20];
        memset(litter_map, -1, sizeof(litter_map));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litter_map[i][j] = litter_cnt++;
                }
            }
        }

        if (litter_cnt == 0) return 0;
        static bool visited[20][20][51][1024];
        memset(visited, 0, sizeof(visited));

        queue<tuple<int, int, int, int, int>> q; 
        int initial_mask = (1 << litter_cnt) - 1;
        q.push({start_r, start_c, max_energy, initial_mask, 0});
        visited[start_r][start_c][max_energy][initial_mask] = true;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, cur_energy, mask, moves] = q.front();
            q.pop();

            if (mask == 0) return moves;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (classroom[nr][nc] == 'X') continue;

                int n_energy = cur_energy - 1;
                if (n_energy < 0) continue;

                int n_mask = mask;
                if (litter_map[nr][nc] != -1) {
                    int bit = litter_map[nr][nc];
                    n_mask &= ~(1 << bit);
                }

                if (n_mask == 0) return moves + 1;

                int final_energy = n_energy;
                if (classroom[nr][nc] == 'R') {
                    final_energy = max_energy;
                }

                if (!visited[nr][nc][final_energy][n_mask]) {
                    visited[nr][nc][final_energy][n_mask] = true;
                    q.push({nr, nc, final_energy, n_mask, moves + 1});
                }
            }
        }

        return -1;
    }
};