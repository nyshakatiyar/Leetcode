class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute costs for every substring
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                // Try every proper divisor
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    // Check each group
                    for (int offset = 0; offset < d; offset++) {
                        int left = i + offset;
                        int right = i + offset
                                  + ((len - 1 - offset) / d) * d;

                        // Compare symmetric characters
                        while (left < right) {
                            if (s[left] != s[right]) {
                                changes++;
                            }

                            left += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // DP: dp[i][j] = minimum changes for first i
        // characters divided into j semi-palindromes
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {
            for (int i = 2 * parts; i <= n; i++) {

                // Start of the last substring
                for (int t = 2 * (parts - 1); t <= i - 2; t++) {

                    if (dp[t][parts - 1] == INF) continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[t][parts - 1] + cost[t][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};