class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr, long long val) -> void {
            if (ql > r || qr < l) return;

            if (ql <= l && r <= qr) {
                sq[node] = (sq[node] + 2 * val * sum[node]
                           + (r - l + 1LL) * val % MOD * val) % MOD;
                sum[node] = (sum[node] + (r - l + 1LL) * val) % MOD;
                lazy[node] = (lazy[node] + val) % MOD;
                return;
            }

            int mid = (l + r) / 2;

            if (lazy[node] != 0) {
                long long v = lazy[node];

                for (int child : {node * 2, node * 2 + 1}) {
                    int len = child == node * 2 ? mid - l + 1 : r - mid;
                    sq[child] = (sq[child] + 2 * v * sum[child]
                                + len * v % MOD * v) % MOD;
                    sum[child] = (sum[child] + len * v) % MOD;
                    lazy[child] = (lazy[child] + v) % MOD;
                }

                lazy[node] = 0;
            }

            self(self, node * 2, l, mid, ql, qr, val);
            self(self, node * 2 + 1, mid + 1, r, ql, qr, val);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        long long ans = 0;
        vector<int> last(100001, -1);

        for (int i = 0; i < n; i++) {
            int p = last[nums[i]] + 1;

            update(update, 1, 0, n - 1, p, i, 1);

            ans = (ans + sq[1]) % MOD;
            last[nums[i]] = i;
        }

        return (int)ans;
    }
};