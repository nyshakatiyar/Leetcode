class Solution {
public:

    struct State {
        long long score = -1;
        vector<int> indices;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.indices < b.indices;   // lexicographically smaller
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // Store: {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(),
             [](const auto& x, const auto& y) {
                 return x[1] < y[1];
             });

        // right endpoints separately for binary search
        vector<long long> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

        /*
            dp[i][k] =
            best answer using first i intervals
            while choosing exactly k intervals.

            i ranges from 0 to n.
            k ranges from 0 to 4.
        */
        vector<vector<State>> dp(n + 1, vector<State>(5));

        // Choosing 0 intervals has score 0
        for (int i = 0; i <= n; i++) {
            dp[i][0].score = 0;
        }

        for (int i = 1; i <= n; i++) {

            long long l = a[i - 1][0];
            long long w = a[i - 1][2];
            int originalIndex = a[i - 1][3];

            // Option 1: don't take this interval
            for (int k = 1; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            /*
                Find how many intervals end strictly before l.

                lower_bound(l) gives first end >= l.
                Therefore all indices before it satisfy:
                    end < l
            */
            int p = lower_bound(ends.begin(), ends.end(), l)
                    - ends.begin();

            // Option 2: take this interval
            for (int k = 1; k <= 4; k++) {

                if (dp[p][k - 1].score == -1)
                    continue;

                State candidate = dp[p][k - 1];

                candidate.score += w;
                candidate.indices.push_back(originalIndex);

                // We need indices sorted for lexicographical comparison
                sort(candidate.indices.begin(),
                     candidate.indices.end());

                if (better(candidate, dp[i][k])) {
                    dp[i][k] = candidate;
                }
            }
        }

        // We want AT MOST 4 intervals.
        State answer;

        for (int k = 1; k <= 4; k++) {
            if (better(dp[n][k], answer)) {
                answer = dp[n][k];
            }
        }

        return answer.indices;
    }
};