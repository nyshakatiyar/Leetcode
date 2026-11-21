class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        // Step 1: Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);
        vector<int> prev(n, -1);

        // Step 2: Iterative DFS on original tree
        // state 0 = entering, state 1 = exiting
        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto [node, state] = st.top();
            st.pop();

            int c = s[node] - 'a';

            if (state == 0) {
                prev[node] = last[c];

                if (last[c] != -1) {
                    newParent[node] = last[c];
                }

                last[c] = node;

                st.push({node, 1});

                for (int child : adj[node]) {
                    st.push({child, 0});
                }
            }
            else {
                last[c] = prev[node];
            }
        }

        // Step 3: Build modified tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        // Get traversal order
        vector<int> order;
        stack<int> stk;
        stk.push(0);

        while (!stk.empty()) {
            int node = stk.top();
            stk.pop();

            order.push_back(node);

            for (int child : tree[node]) {
                stk.push(child);
            }
        }

        // Calculate subtree sizes in reverse order
        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int node = order[i];

            for (int child : tree[node]) {
                ans[node] += ans[child];
            }
        }

        return ans;
    }
};