class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);

        for (auto &e : invocations) {
            graph[e[0]].push_back(e[1]);
        }

        vector<bool> suspicious(n, false);

        // DFS to mark all suspicious methods
        function<void(int)> dfs = [&](int u) {
            suspicious[u] = true;
            for (int v : graph[u]) {
                if (!suspicious[v]) {
                    dfs(v);
                }
            }
        };

        dfs(k);

        // If any outside method calls a suspicious method,
        // removal is impossible.
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Return remaining methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};