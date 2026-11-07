
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // Available servers: {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // Busy servers: {free time, index}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        // Initially, all servers are available.
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);
        long long time = 0;

        for (int j = 0; j < m; j++) {

            // Current time cannot be earlier than task arrival.
            time = max(time, (long long)j);

            // Release all servers that have finished.
            while (!busy.empty() && busy.top().first <= time) {
                auto [freeTime, idx] = busy.top();
                busy.pop();

                available.push({servers[idx], idx});
            }

            // If no server is available, wait.
            if (available.empty()) {
                time = busy.top().first;

                // Release all servers finishing at this time.
                while (!busy.empty() && busy.top().first <= time) {
                    auto [freeTime, idx] = busy.top();
                    busy.pop();

                    available.push({servers[idx], idx});
                }
            }

            // Choose the server with minimum weight, then index.
            auto [weight, serverIdx] = available.top();
            available.pop();

            ans[j] = serverIdx;

            // Mark the server as busy.
            busy.push({time + tasks[j], serverIdx});
        }

        return ans;
    }
};