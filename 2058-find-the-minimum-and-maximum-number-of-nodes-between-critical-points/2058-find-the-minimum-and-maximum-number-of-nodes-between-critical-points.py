class Solution:
    def nodesBetweenCriticalPoints(self, head):
        # Need at least 3 nodes for a critical point
        if head is None or head.next is None or head.next.next is None:
            return [-1, -1]

        prev = head
        curr = head.next

        index = 1

        first = -1
        last = -1
        minDist = float('inf')

        while curr.next:
            # Check whether curr is a critical point
            is_max = curr.val > prev.val and curr.val > curr.next.val
            is_min = curr.val < prev.val and curr.val < curr.next.val

            if is_max or is_min:
                if first == -1:
                    # First critical point
                    first = index
                else:
                    # Distance from previous critical point
                    minDist = min(minDist, index - last)

                last = index

            prev = curr
            curr = curr.next
            index += 1

        # Fewer than two critical points
        if first == last:
            return [-1, -1]

        maxDist = last - first

        return [minDist, maxDist]