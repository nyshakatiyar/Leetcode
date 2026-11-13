class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n)
            LOG++;

        // Prefix sums
        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        // Next strictly greater element
        vector<int> nge(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                nge[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        // Binary lifting tables
        vector<vector<int>> up(LOG, vector<int>(n, -1));
        vector<vector<long long>> sum(LOG, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nge[i];

            if (nge[i] != -1) {
                sum[0][i] =
                    1LL * nums[i] * (nge[i] - i)
                    - (pref[nge[i]] - pref[i]);
            }
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                if (mid != -1 && up[j - 1][mid] != -1) {
                    up[j][i] = up[j - 1][mid];

                    sum[j][i] =
                        sum[j - 1][i] + sum[j - 1][mid];
                }
            }
        }

        // Calculate cost of subarray [l, r]
        auto getCost = [&](int l, int r) -> long long {
            long long cost = 0;
            int p = l;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][p] != -1 && up[j][p] <= r) {
                    cost += sum[j][p];
                    p = up[j][p];
                }
            }

            // Remaining segment
            cost += 1LL * nums[p] * (r - p + 1)
                    - (pref[r + 1] - pref[p]);

            return cost;
        };

        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int lo = 0, hi = r;

            // Find the smallest valid left endpoint
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (getCost(mid, r) <= k)
                    hi = mid;
                else
                    lo = mid + 1;
            }

            ans += r - lo + 1;
        }

        return ans;
    }
};