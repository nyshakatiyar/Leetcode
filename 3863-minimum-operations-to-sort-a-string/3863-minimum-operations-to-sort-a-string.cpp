class Solution {
public:
    int minOperations(string s) {
        string t = s;
        sort(t.begin(), t.end());

        if (s == t) return 0;

        int n = s.size();

        if (n == 2) return -1;

        if (n == 3) {
            queue<pair<string, int>> q;
            unordered_set<string> vis;

            q.push({s, 0});
            vis.insert(s);

            while (!q.empty()) {
                auto [cur, steps] = q.front();
                q.pop();

                if (cur == t) return steps;

                for (int i = 0; i < 2; i++) {
                    string nxt = cur;
                    sort(nxt.begin() + i, nxt.begin() + i + 2);

                    if (vis.insert(nxt).second) {
                        q.push({nxt, steps + 1});
                    }
                }
            }

            return -1;
        }

        if (s[0] == t[0] || s[n - 1] == t[n - 1])
            return 1;

        // Three operations are needed only when the first
        // character is uniquely the maximum and the last
        // character is uniquely the minimum.
        char mn = t[0], mx = t[n - 1];

        int minCount = count(s.begin(), s.end(), mn);
        int maxCount = count(s.begin(), s.end(), mx);

        if (s[0] == mx && s[n - 1] == mn &&
            minCount == 1 && maxCount == 1)
            return 3;

        return 2;
    }
};