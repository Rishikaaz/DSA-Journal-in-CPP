class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        // Memoization table initialized to -1
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        
        return dfs(piles, suffixSum, memo, 0, 1);
    }
    
private:
    int dfs(const vector<int>& piles, const vector<int>& suffixSum, vector<vector<int>>& memo, int i, int M) {
        int n = piles.size();
        if (i + 2 * M >= n) {
            return suffixSum[i];
        }
        if (memo[i][M] != -1) {
            return memo[i][M];
        }
        
        int maxStones = 0;
        // Try all possible valid X moves (1 <= X <= 2M)
        for (int X = 1; X <= 2 * M; ++X) {
            int opponentStones = dfs(piles, suffixSum, memo, i + X, max(M, X));
            int currentStones = suffixSum[i] - opponentStones;
            maxStones = max(maxStones, currentStones);
        }
        
        return memo[i][M] = maxStones;
    }
};
