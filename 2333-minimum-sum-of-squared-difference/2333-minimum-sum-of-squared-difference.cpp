class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        
        long long k = (long long)k1 + k2;

        // Maximum possible difference is 100000.
        vector<long long> freq(100001, 0);

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            freq[d]++;
        }

        // Reduce the largest differences first.
        for (int d = 100000; d > 0 && k > 0; d--) {

            if (freq[d] == 0)
                continue;

            long long cnt = freq[d];

            // Number of operations needed to move
            // all differences d -> d-1
            long long operations = min(k, cnt);

            // Move 'operations' elements from d to d-1.
            freq[d] -= operations;
            freq[d - 1] += operations;

            k -= operations;

            // If k is still large, the loop will continue
            // and process the next level.
        }

        long long ans = 0;

        for (int d = 1; d <= 100000; d++) {
            ans += freq[d] * d * d;
        }

        return ans;
    }
};