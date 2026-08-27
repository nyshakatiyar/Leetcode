class Solution:
    def lexGreaterPermutation(self, s, target):
        # Frequency of characters in s
        freq = [0] * 26

        for ch in s:
            freq[ord(ch) - ord('a')] += 1

        n = len(s)

        # Try making the first difference at position i
        # from right to left.
        for i in range(n - 1, -1, -1):

            # We need the prefix target[0...i-1].
            # Temporarily remove those characters from freq.
            if i < n:
                # Start with the original frequencies again
                freq = [0] * 26
                for ch in s:
                    freq[ord(ch) - ord('a')] += 1

                possible = True

                for j in range(i):
                    x = ord(target[j]) - ord('a')

                    if freq[x] == 0:
                        possible = False
                        break

                    freq[x] -= 1

                if not possible:
                    continue

            # Find the smallest character > target[i]
            target_char = ord(target[i]) - ord('a')

            bigger = -1

            for c in range(target_char + 1, 26):
                if freq[c] > 0:
                    bigger = c
                    break

            if bigger == -1:
                continue

            # Use this character at position i
            freq[bigger] -= 1

            # Fill the rest with smallest possible characters
            result = target[:i] + chr(bigger + ord('a'))

            for c in range(26):
                result += chr(c + ord('a')) * freq[c]

            return result

        return ""