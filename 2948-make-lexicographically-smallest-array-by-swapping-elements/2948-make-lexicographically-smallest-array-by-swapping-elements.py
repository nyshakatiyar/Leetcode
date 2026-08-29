class Solution:
    def lexicographicallySmallestArray(self, nums, limit):
        n = len(nums)

        # (value, original index)
        arr = sorted((nums[i], i) for i in range(n))

        ans = nums[:]

        start = 0

        while start < n:
            end = start

            # Find one connected group
            while end + 1 < n and arr[end + 1][0] - arr[end][0] <= limit:
                end += 1

            # Values in this group
            values = [arr[i][0] for i in range(start, end + 1)]

            # Original indices in this group
            indices = [arr[i][1] for i in range(start, end + 1)]

            # Smallest values should go to smallest indices
            indices.sort()

            for i in range(len(values)):
                ans[indices[i]] = values[i]

            start = end + 1

        return ans