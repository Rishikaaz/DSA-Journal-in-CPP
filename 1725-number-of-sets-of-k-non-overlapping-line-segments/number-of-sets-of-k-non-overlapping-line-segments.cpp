class Solution {
public:
    long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n, long long mod) {
        return power(n, mod - 2, mod);
    }

    int numberOfSets(int n, int k) {
        long long MOD = 1e9 + 7;
        int totalN = n + k - 1;
        int totalR = 2 * k;

        if (totalR > totalN) return 0;

        long long num = 1, den = 1;
        for (int i = 0; i < totalR; ++i) {
            num = (num * (totalN - i)) % MOD;
            den = (den * (i + 1)) % MOD;
        }

        return (num * modInverse(den, MOD)) % MOD;
    }
};