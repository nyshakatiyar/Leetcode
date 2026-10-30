class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                string labels, int k) {

        vector<vector<pair<int, int>>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        // dist[node][count] = minimum cost to reach node
        // with count consecutive occurrences of its label.
        const long long INF = LLONG_MAX;

        vector<vector<long long>> dist(n,
                                       vector<long long>(k + 1, INF));

        // {cost, node, consecutive count}
        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, cnt] = pq.top();
            pq.pop();

            if (cost != dist[u][cnt])
                continue;

            if (u == n - 1)
                return (int)cost;

            for (auto [v, w] : adj[u]) {

                int newCnt;

                if (labels[u] == labels[v]) {
                    newCnt = cnt + 1;
                } else {
                    newCnt = 1;
                }

                if (newCnt > k)
                    continue;

                long long newCost = cost + w;

                if (newCost < dist[v][newCnt]) {
                    dist[v][newCnt] = newCost;
                    pq.push({newCost, v, newCnt});
                }
            }
        }

        return -1;
    }
};