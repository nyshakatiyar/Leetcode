class Solution(object):
    def firstStableIndex(self, nums, k):
        n = len(nums)

        # suffix[i] = minimum value from i to the end
        suffix = [0] * n
        suffix[n - 1] = nums[n - 1]

        for i in range(n - 2, -1, -1):
            suffix[i] = min(nums[i], suffix[i + 1])

        # Find the prefix maximum while going left to right
        prefix_max = nums[0]

        for i in range(n):
            prefix_max = max(prefix_max, nums[i])

            instability = prefix_max - suffix[i]

            if instability <= k:
                return i

        return -1

