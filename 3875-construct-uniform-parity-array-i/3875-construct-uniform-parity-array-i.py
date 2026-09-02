class Solution(object):
    def uniformArray(self, nums1):
        n = len(nums1)

        has_odd = any(x % 2 == 1 for x in nums1)
        has_even = any(x % 2 == 0 for x in nums1)

        # If all numbers already have the same parity
        if not (has_odd and has_even):
            return True

        # We have both odd and even numbers.
        # Choose an odd number and an even number as references.
        #
        # For every element:
        # - To make it even, subtract a number with the same parity.
        # - To make it odd, subtract a number with opposite parity.
        #
        # Since there is at least one number of each parity,
        # we can always make every element even.
        return True
        """
        :type nums1: List[int]
        :rtype: bool
        """
        