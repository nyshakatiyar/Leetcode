class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> adj(n + 1);

        for (auto &r : roads) {
            int u = r[0], v = r[1], w = r[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;

        int ans = INT_MAX;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &[v, w] : adj[u]) {
                ans = min(ans, w);

                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }

        return ans;
    }
};