class Solution(object):
    def uniformArray(self, nums1):
        mn = min(nums1)

        if mn % 2 == 1:
            return True

        for x in nums1:
            if x % 2 == 1:
                return False

        return True