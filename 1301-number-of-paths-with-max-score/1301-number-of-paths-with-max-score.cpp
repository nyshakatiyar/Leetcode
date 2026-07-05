class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();

        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == 'X' || (i == n - 1 && j == n - 1))
                    continue;

                int best = -1;
                long long cnt = 0;

                vector<pair<int,int>> prev = {
                    {i + 1, j},
                    {i, j + 1},
                    {i + 1, j + 1}
                };

                for (auto [x, y] : prev) {
                    if (x >= n || y >= n) continue;
                    if (score[x][y] == -1) continue;

                    if (score[x][y] > best) {
                        best = score[x][y];
                        cnt = ways[x][y];
                    } else if (score[x][y] == best) {
                        cnt = (cnt + ways[x][y]) % MOD;
                    }
                }

                if (best == -1) continue;

                int val = 0;
                if (board[i][j] >= '1' && board[i][j] <= '9')
                    val = board[i][j] - '0';

                score[i][j] = best + val;
                ways[i][j] = cnt % MOD;
            }
        }

        if (ways[0][0] == 0)
            return {0, 0};

        return {score[0][0], ways[0][0]};
    }
};