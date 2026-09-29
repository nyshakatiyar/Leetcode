class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int len = m + n - 1;

        // Valid parentheses string must have even length
        if (len % 2 == 1)
            return false;

        // Must start with '('
        if (grid[0][0] == ')')
            return false;

        vector<vector<bool>> dp(
            n,
            vector<bool>(len + 1, false)
        );

        // Starting cell has balance 1
        dp[0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                // IMPORTANT:
                // Remove states left from the previous row
                vector<bool> current(len + 1, false);

                int delta = (grid[i][j] == '(') ? 1 : -1;

                for (int bal = 0; bal <= len; bal++) {

                    int prev = bal - delta;

                    if (prev < 0)
                        continue;

                    // From top
                    if (i > 0 && dp[j][prev]) {
                        current[bal] = true;
                    }

                    // From left
                    if (j > 0 && dp[j - 1][prev]) {
                        current[bal] = true;
                    }
                }

                // Replace old column state
                dp[j] = current;
            }
        }

        return dp[n - 1][0];
    }
};