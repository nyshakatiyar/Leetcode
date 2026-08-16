class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int c0 = cnt[0];
        int c1 = cnt[1];
        int c2 = cnt[2];

        // If there are no stones of one of the non-zero remainders
        if (c1 == 0 || c2 == 0) {
            // Alice must start with the only available non-zero type.
            // She can win only if there are enough of them and
            // the number of 0-remainder stones is odd.
            return max(c1, c2) > 2 && (c0 % 2 == 1);
        }

        // Both remainder 1 and remainder 2 stones exist.
        //
        // If the difference is greater than 2, Alice can force
        // the opponent to take a stone that makes the sum divisible by 3.
        //
        // Otherwise, the parity of the 0-remainder stones determines
        // who can control the game.
        return abs(c1 - c2) > 2 || (c0 % 2 == 0);
    }
};