from collections import deque

class Solution:
    def minMoves(self, classroom, energy):
        m = len(classroom)
        n = len(classroom[0])

        # Find start and assign each litter an ID
        start = None
        litter = {}

        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'S':
                    start = (i, j)
                elif classroom[i][j] == 'L':
                    litter[(i, j)] = len(litter)

        total = len(litter)

        # No litter to collect
        if total == 0:
            return 0

        full_mask = (1 << total) - 1

        # best[r][c][mask] = maximum energy with which
        # we've reached this position having collected mask.
        best = [
            [
                [-1] * (1 << total)
                for _ in range(n)
            ]
            for _ in range(m)
        ]

        sr, sc = start
        best[sr][sc][0] = energy

        # row, col, mask, remaining_energy, distance
        q = deque([(sr, sc, 0, energy, 0)])

        directions = [
            (1, 0),
            (-1, 0),
            (0, 1),
            (0, -1)
        ]

        while q:
            r, c, mask, e, dist = q.popleft()

            for dr, dc in directions:
                nr = r + dr
                nc = c + dc

                # Outside grid
                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue

                # Obstacle
                if classroom[nr][nc] == 'X':
                    continue

                # Can't move if we have no energy
                if e == 0:
                    continue

                ne = e - 1
                nmask = mask

                # Collect litter
                if classroom[nr][nc] == 'L':
                    idx = litter[(nr, nc)]
                    nmask |= (1 << idx)

                # Reset energy on R
                if classroom[nr][nc] == 'R':
                    ne = energy

                # All litter collected
                if nmask == full_mask:
                    return dist + 1

                # If we've already reached this state with
                # at least as much energy, this state is useless.
                if best[nr][nc][nmask] >= ne:
                    continue

                best[nr][nc][nmask] = ne
                q.append((nr, nc, nmask, ne, dist + 1))

        return -1