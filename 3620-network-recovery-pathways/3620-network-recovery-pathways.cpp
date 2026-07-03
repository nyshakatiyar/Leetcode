class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n, 0);

        int mxCost = 0;
        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            indeg[e[1]]++;
            mxCost = max(mxCost, e[2]);
        }

        // Topological order
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
                q.push(i);

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, c] : adj[u]) {
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }

        auto check = [&](int lim) {
            const long long INF = (1LL << 60);
            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF) continue;
                if (u != 0 && u != n - 1 && !online[u]) continue;

                for (auto &[v, c] : adj[u]) {
                    if (c < lim) continue;
                    if (v != n - 1 && !online[v]) continue;

                    if (dist[u] + c < dist[v])
                        dist[v] = dist[u] + c;
                }
            }

            return dist[n - 1] <= k;
        };

        if (!check(0)) return -1;

        int lo = 0, hi = mxCost, ans = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};