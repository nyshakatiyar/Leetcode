class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        // Store reserved seats as a bitmask
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            // Only seats 2-9 matter
            if (s >= 2 && s <= 9) {
                rows[row] |= (1 << s);
            }
        }

        // Initially assume every row can fit 2 groups
        long long ans = 2LL * n;

        for (auto &[row, mask] : rows) {
            int groups = 0;

            // Seats 2,3,4,5
            bool left =
                !(mask & (1 << 2)) &&
                !(mask & (1 << 3)) &&
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5));

            // Seats 6,7,8,9
            bool right =
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7)) &&
                !(mask & (1 << 8)) &&
                !(mask & (1 << 9));

            // Seats 4,5,6,7
            bool middle =
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5)) &&
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7));

            if (left && right) {
                groups = 2;
            }
            else if (left || middle || right) {
                groups = 1;
            }

            // This row was counted as 2 initially
            ans -= 2;
            ans += groups;
        }

        return (int)ans;
    }
};