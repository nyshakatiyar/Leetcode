#include <string>
#include <array>
using namespace std;

class Solution {
public:
    string smallestPalindrome(string s, long long k) {
        int n = s.size();
        array<long long, 26> freq{};
        for (char c : s) freq[c - 'a']++;

        char middle = 0;
        array<long long, 26> halfCounts{};
        int halfLen = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 == 1) middle = 'a' + i;
            halfCounts[i] = freq[i] / 2;
            halfLen += halfCounts[i];
        }

        auto permsCapped = [&](array<long long,26>& counts, int length, long long cap) -> long long {
            if (length == 0) return 1;
            int distinctCount = 0;
            for (int i = 0; i < 26; i++) if (counts[i] > 0) distinctCount++;
            if (distinctCount <= 1) return 1;

            long long result = 1;
            long long total = 0;
            for (int i = 0; i < 26; i++) {
                long long c = counts[i];
                if (c == 0) continue;
                total += c;
                long long comb = 1;
                for (long long j = 1; j <= c; j++) {
                    comb = comb * (total - c + j) / j;
                    if (comb > cap) return cap + 1;
                }
                result *= comb;
                if (result > cap) return cap + 1;
            }
            return result;
        };

        if (permsCapped(halfCounts, halfLen, k) < k) return "";

        array<long long,26> counts = halfCounts;
        int remaining = halfLen;
        string resultChars;

        for (int pos = 0; pos < halfLen; pos++) {
            for (int i = 0; i < 26; i++) {
                if (counts[i] == 0) continue;
                counts[i]--;
                long long cnt = permsCapped(counts, remaining - 1, k);
                if (cnt >= k) {
                    resultChars += (char)('a' + i);
                    remaining--;
                    break;
                } else {
                    k -= cnt;
                    counts[i]++;
                }
            }
        }

        string halfStr = resultChars;
        string reversedHalf = halfStr;
        reverse(reversedHalf.begin(), reversedHalf.end());

        string ans = halfStr;
        if (middle) ans += middle;
        ans += reversedHalf;
        return ans;
    }
};