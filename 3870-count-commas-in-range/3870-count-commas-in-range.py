
class Solution(object):
    def countCommas(self, n):
        ans = 0

        for i in range(1, n + 1):
            if i >= 1000:
                ans += (len(str(i)) - 1) // 3

        return ans

