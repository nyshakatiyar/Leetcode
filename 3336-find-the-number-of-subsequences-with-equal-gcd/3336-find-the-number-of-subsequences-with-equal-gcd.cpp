class Solution {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {
        const int MAXG = 200;

        vector<vector<int>> dp(MAXG + 1, vector<int>(MAXG + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp = dp;

            for (int g1 = 0; g1 <= MAXG; g1++) {
                for (int g2 = 0; g2 <= MAXG; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    // Put x into seq1
                    int ng1 = (g1 == 0 ? x : gcd(g1, x));
                    ndp[ng1][g2] = (ndp[ng1][g2] + dp[g1][g2]) % MOD;

                    // Put x into seq2
                    int ng2 = (g2 == 0 ? x : gcd(g2, x));
                    ndp[g1][ng2] = (ndp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAXG; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};