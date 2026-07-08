class Solution {
public:
    static const int MOD = 1000000007;

    struct Node {
        int len;
        long long val;
        long long sum;
        Node(int l = 0, long long v = 0, long long s = 0)
            : len(l), val(v), sum(s) {}
    };

    vector<Node> seg;
    vector<long long> pw;
    string str;

    Node merge(const Node &a, const Node &b) {
        Node res;
        res.len = a.len + b.len;
        res.sum = a.sum + b.sum;
        res.val = (a.val * pw[b.len] + b.val) % MOD;
        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            int d = str[l] - '0';
            if (d == 0)
                seg[idx] = Node(0, 0, 0);
            else
                seg[idx] = Node(1, d, d);
            return;
        }

        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(idx * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(idx * 2 + 1, mid + 1, r, ql, qr);

        return merge(query(idx * 2, l, mid, ql, qr),
                     query(idx * 2 + 1, mid + 1, r, ql, qr));
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        str = s;
        int n = s.size();

        pw.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pw[i] = pw[i - 1] * 10 % MOD;

        seg.assign(4 * n + 5, Node());
        build(1, 0, n - 1);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            Node cur = query(1, 0, n - 1, q[0], q[1]);
            ans.push_back((cur.val * (cur.sum % MOD)) % MOD);
        }

        return ans;
    }
};