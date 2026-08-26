class Solution:
    def shortestBeautifulSubstring(self, s, k) :
        positions = []

        # Store positions of all 1s
        for i in range(len(s)):
            if s[i] == '1':
                positions.append(i)

        # Not enough 1s
        if len(positions) < k:
            return ""

        best = ""

        # Consider every group of k consecutive 1s
        for i in range(k - 1, len(positions)):
            left = positions[i - k + 1]
            right = positions[i]

            curr = s[left:right + 1]

            if (best == "" or
                len(curr) < len(best) or
                (len(curr) == len(best) and curr < best)):
                best = curr

        return best