class Solution {
public:
    struct Node {
        int len;
        int left, right, best;
        char lc, rc;

        Node() : len(0), left(0), right(0), best(0), lc(0), rc(0) {}

        Node(char c) {
            len = left = right = best = 1;
            lc = rc = c;
        }
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.left = a.left;
        res.right = b.right;
        res.best = max(a.best, b.best);

        if (a.rc == b.lc) {
            // Join suffix of a with prefix of b
            res.best = max(res.best, a.right + b.left);

            // Entire left segment has the same character
            if (a.left == a.len)
                res.left = a.len + b.left;

            // Entire right segment has the same character
            if (b.right == b.len)
                res.right = b.len + a.right;
        }

        return res;
    }

    void build(int node, int l, int r, string &s) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        int n = s.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int idx = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, idx, c);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};