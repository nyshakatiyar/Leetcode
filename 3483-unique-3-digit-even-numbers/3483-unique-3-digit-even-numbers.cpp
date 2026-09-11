class Solution {
public:
    int totalNumbers(vector<int>& digits) {

        int freq[10] = {0};

        // Count available copies of each digit
        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // Generate every 3-digit even number
        for (int num = 100; num <= 998; num += 2) {

            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            int need[10] = {0};

            need[a]++;
            need[b]++;
            need[c]++;

            bool possible = true;

            // Check whether we have enough copies
            for (int d = 0; d <= 9; d++) {
                if (need[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};