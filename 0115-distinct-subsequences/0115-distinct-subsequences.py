class Solution:
    def numDistinct(self, s, t) :
        m, n = len(s), len(t)

        # dp[j] = number of ways to form t[:j] from
        # characters processed so far in s
        dp = [0] * (n + 1)
        dp[0] = 1

        for i in range(m):
            # Go backwards so dp[j-1] is still from the
            # previous set of characters in s.
            for j in range(n, 0, -1):
                if s[i] == t[j - 1]:
                    dp[j] += dp[j - 1]

        return dp[n]