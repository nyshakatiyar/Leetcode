class Solution:
    def missingMultiple(self, nums, k) :
        seen = set(nums)

        multiple = k

        while multiple in seen:
            multiple += k

        return multiple