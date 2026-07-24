class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<char>> dp(4, vector<char>(MAXX, 0));
        dp[0][0] = 1;

        for (int v : nums) {
            auto ndp = dp;

            for (int cnt = 0; cnt <= 3; cnt++) {
                for (int x = 0; x < MAXX; x++) {
                    if (!dp[cnt][x]) continue;

                    for (int take = 1; take + cnt <= 3; take++) {
                        int nx = x ^ ((take & 1) ? v : 0);
                        ndp[cnt + take][nx] = 1;
                    }
                }
            }

            dp.swap(ndp);
        }

        int ans = 0;
        for (int x = 0; x < MAXX; x++)
            ans += dp[3][x];

        return ans;
    }
};