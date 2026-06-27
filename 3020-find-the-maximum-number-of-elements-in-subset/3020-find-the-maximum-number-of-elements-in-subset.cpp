class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        for (int x : nums) freq[x]++;

        int ans = 1;

        // Handle 1 separately since 1^2 = 1
        if (freq.count(1)) {
            int c = freq[1];
            ans = max(ans, (c % 2 == 0) ? c - 1 : c);
        }

        for (auto &[start, cnt] : freq) {
            if (start == 1) continue;

            long long cur = start;
            int len = 0;

            while (true) {
                if (!freq.count(cur) || freq[cur] == 0) break;

                if (freq[cur] == 1) {
                    len += 1;          // current becomes the center
                    break;
                }

                // freq[cur] >= 2
                if (cur > 1000000000LL / cur ||
                    !freq.count(cur * cur) ||
                    freq[cur * cur] == 0) {
                    len += 1;          // stop here, use one copy as center
                    break;
                }

                len += 2;              // use two copies and continue
                cur = cur * cur;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};