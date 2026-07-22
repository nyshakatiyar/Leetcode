#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Group {
        int start;
        int length;
    };

    class SparseTable {
    public:
        SparseTable(const vector<int>& nums) {
            int n = nums.size();
            if (n == 0) return;
            int K = __lg(n) + 1;
            st.assign(K, vector<int>(n));
            st[0] = nums;
            for (int k = 1; k < K; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    st[k][i] = max(st[k - 1][i],
                                   st[k - 1][i + (1 << (k - 1))]);
                }
            }
        }

        int query(int l, int r) {
            if (l > r) return 0;
            int k = __lg(r - l + 1);
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        }

    private:
        vector<vector<int>> st;
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int ones = count(s.begin(), s.end(), '1');

        auto [zeroGroups, zeroGroupIndex] = getZeroGroups(s);

        if (zeroGroups.empty())
            return vector<int>(queries.size(), ones);

        SparseTable st(getZeroMergeLengths(zeroGroups));

        vector<int> ans;

        for (auto& q : queries) {
            int l = q[0], r = q[1];

            int left =
                zeroGroupIndex[l] == -1
                    ? -1
                    : zeroGroups[zeroGroupIndex[l]].length -
                          (l - zeroGroups[zeroGroupIndex[l]].start);

            int right =
                zeroGroupIndex[r] == -1
                    ? -1
                    : r - zeroGroups[zeroGroupIndex[r]].start + 1;

            auto p = mapToAdjacentGroupIndices(
                zeroGroupIndex[l] + 1,
                s[r] == '1' ? zeroGroupIndex[r]
                            : zeroGroupIndex[r] - 1);

            int L = p.first;
            int R = p.second;

            int cur = ones;

            if (s[l] == '0' && s[r] == '0' &&
                zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                cur = max(cur, ones + left + right);
            } else if (L <= R) {
                cur = max(cur, ones + st.query(L, R));
            }

            if (s[l] == '0' &&
                zeroGroupIndex[l] + 1 <=
                    (s[r] == '1' ? zeroGroupIndex[r]
                                 : zeroGroupIndex[r] - 1)) {
                cur = max(cur,
                          ones + left +
                              zeroGroups[zeroGroupIndex[l] + 1].length);
            }

            if (s[r] == '0' &&
                zeroGroupIndex[l] < zeroGroupIndex[r] - 1) {
                cur = max(cur,
                          ones + right +
                              zeroGroups[zeroGroupIndex[r] - 1].length);
            }

            ans.push_back(cur);
        }

        return ans;
    }

private:
    pair<vector<Group>, vector<int>> getZeroGroups(string& s) {
        vector<Group> groups;
        vector<int> idx(s.size());

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                if (i && s[i - 1] == '0')
                    groups.back().length++;
                else
                    groups.push_back({i, 1});
            }
            idx[i] = (int)groups.size() - 1;
        }

        return {groups, idx};
    }

    vector<int> getZeroMergeLengths(vector<Group>& groups) {
        vector<int> res;
        for (int i = 0; i + 1 < groups.size(); i++)
            res.push_back(groups[i].length + groups[i + 1].length);
        return res;
    }

    pair<int, int> mapToAdjacentGroupIndices(int l, int r) {
        return {l, r - 1};
    }
};