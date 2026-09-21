class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {

        vector<long long> dp(k, 0);
        vector<long long> ans(k, 0);

        for (int num : nums) {

            int val = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray with just this element
            newDp[val]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {

                int newRemainder = (r * val) % k;

                newDp[newRemainder] += dp[r];
            }

            // Add all subarrays ending here to the answer
            for (int r = 0; r < k; r++) {
                ans[r] += newDp[r];
            }

            dp = newDp;
        }

        return ans;
    }
};