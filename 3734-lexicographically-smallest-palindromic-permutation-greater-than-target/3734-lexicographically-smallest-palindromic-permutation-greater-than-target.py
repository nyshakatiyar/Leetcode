class Solution:
    def lexPalindromicPermutation(self, s, target):
        n = len(s)

        # Count characters
        freq = [0] * 26
        for ch in s:
            freq[ord(ch) - ord('a')] += 1

        # More than one odd frequency -> no palindrome possible
        odd = 0
        middle = ''

        for i in range(26):
            if freq[i] % 2:
                odd += 1
                middle = chr(i + ord('a'))

        if odd > 1:
            return ""

        # Characters used in the first half
        half_freq = [x // 2 for x in freq]
        half_len = n // 2

        target_half = target[:half_len]

        # ------------------------------------------------
        # Try using target's first half exactly
        # ------------------------------------------------
        remaining = half_freq[:]
        possible = True

        for ch in target_half:
            idx = ord(ch) - ord('a')

            if remaining[idx] == 0:
                possible = False
                break

            remaining[idx] -= 1

        if possible:
            half = target_half

            if n % 2:
                candidate = half + middle + half[::-1]
            else:
                candidate = half + half[::-1]

            if candidate > target:
                return candidate

        # ------------------------------------------------
        # Find the smallest half > target_half
        # Try changing the rightmost possible position
        # ------------------------------------------------
        for i in range(half_len - 1, -1, -1):

            remaining = half_freq[:]
            possible = True

            # Match target_half[0 ... i-1]
            for j in range(i):
                idx = ord(target_half[j]) - ord('a')

                if remaining[idx] == 0:
                    possible = False
                    break

                remaining[idx] -= 1

            if not possible:
                continue

            # Find smallest character greater than target[i]
            cur = ord(target_half[i]) - ord('a')
            bigger = -1

            for c in range(cur + 1, 26):
                if remaining[c] > 0:
                    bigger = c
                    break

            if bigger == -1:
                continue

            remaining[bigger] -= 1

            # Build smallest possible half
            half = target_half[:i] + chr(bigger + ord('a'))

            for c in range(26):
                half += chr(c + ord('a')) * remaining[c]

            # Build palindrome
            if n % 2:
                candidate = half + middle + half[::-1]
            else:
                candidate = half + half[::-1]

            if candidate > target:
                return candidate

        return ""