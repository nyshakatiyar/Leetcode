class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;

        int primes[] = {2, 3, 5, 7};

        for (int i = 0; i < n; i++) {
            int sum[4] = {0, 0, 0, 0};
            int mn[4] = {100, 100, 100, 100};
            int mx[4] = {0, 0, 0, 0};

            for (int j = i; j < n; j++) {
                int x = nums[j];

                for (int p = 0; p < 4; p++) {
                    int cnt = 0;

                    while (x % primes[p] == 0) {
                        cnt++;
                        x /= primes[p];
                    }

                    sum[p] += cnt;
                    mn[p] = min(mn[p], cnt);
                    mx[p] = max(mx[p], cnt);
                }

                bool valid = true;

                for (int p = 0; p < 4; p++) {
                    if (sum[p] != mn[p] + mx[p]) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};