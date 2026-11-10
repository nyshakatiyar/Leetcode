class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int jump = 1; jump <= 3; jump++) {

                int prev = i - jump;

                if (prev >= 0) {
                    int cost = costs[i - 1] + jump * jump;

                    dp[i] = min(dp[i], dp[prev] + cost);
                }
            }
        }

        return dp[n];
    }
};