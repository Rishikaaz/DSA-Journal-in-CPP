class Solution {
public:
    int distinctSubseqII(string s) {
        long long MOD = 1e9 + 7;
        int n = s.length();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        
        vector<int> last(26, -1);
        
        for (int i = 1; i <= n; ++i) {
            int x = s[i - 1] - 'a';
            dp[i] = (2 * dp[i - 1]) % MOD;
            
            if (last[x] != -1) {
                dp[i] = (dp[i] - dp[last[x] - 1] + MOD) % MOD;
            }
            
            last[x] = i;
        }
        
        return (dp[n] - 1 + MOD) % MOD;
    }
};