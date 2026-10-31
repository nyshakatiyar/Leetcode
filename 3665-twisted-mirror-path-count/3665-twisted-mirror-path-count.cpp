class Solution {
public:
    const int MOD = 1e9 + 7;

    int m, n;

    // memo[r][c][d]:
    // Final destination after entering (r,c) in direction d.
    // d = 0 means right, d = 1 means down.
    vector<vector<array<int, 2>>> memo;

    int solve(int r, int c, int d, vector<vector<int>>& grid) {
        if (r >= m || c >= n)
            return -1;

        if (grid[r][c] == 0)
            return r * n + c;

        if (memo[r][c][d] != -2)
            return memo[r][c][d];

        int ans;

        if (d == 0) {
            // Entered mirror moving right.
            // Redirect down.
            ans = solve(r + 1, c, 1, grid);
        } 
        else {
            // Entered mirror moving down.
            // Redirect right.
            ans = solve(r, c + 1, 0, grid);
        }

        return memo[r][c][d] = ans;
    }

    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        memo.assign(m, vector<array<int, 2>>(n, {-2, -2}));

        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0)
                    continue;

                // Try moving right.
                int right = solve(i, j + 1, 0, grid);

                if (right != -1) {
                    int r = right / n;
                    int c = right % n;

                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }

                // Try moving down.
                int down = solve(i + 1, j, 1, grid);

                if (down != -1) {
                    int r = down / n;
                    int c = down % n;

                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};