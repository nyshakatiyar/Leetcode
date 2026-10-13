class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        vector<long long> squares;

        for (int x : nums) {
            squares.push_back(1LL * x * x);
        }

        sort(squares.begin(), squares.end());

        long long ans = 0;

        // Largest ceil(n/2) values get '+'
        int positive = (n + 1) / 2;

        for (int i = 0; i < n; i++) {
            if (i >= n - positive) {
                ans += squares[i];
            } else {
                ans -= squares[i];
            }
        }

        return ans;
    }
};
