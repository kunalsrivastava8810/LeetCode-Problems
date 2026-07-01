class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        const int INF = 1e9;

        vector<vector<int>> dist(n, vector<int>(n, INF));
        queue<pair<int,int>> q;

        // Multi-source BFS from all thieves.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dirs[5] = {1, 0, -1, 0, 1};
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++) {
                int nx = x + dirs[k];
                int ny = y + dirs[k + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    dist[nx][ny] == INF) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // Widest path (maximize the minimum safeness along the path).
        vector<vector<int>> best(n, vector<int>(n, -1));
        priority_queue<tuple<int,int,int>> pq;
        best[0][0] = dist[0][0];
        pq.push({best[0][0], 0, 0});

        while (!pq.empty()) {
            auto [safe, x, y] = pq.top();
            pq.pop();

            if (x == n - 1 && y == n - 1) return safe;
            if (safe < best[x][y]) continue;

            for (int k = 0; k < 4; k++) {
                int nx = x + dirs[k];
                int ny = y + dirs[k + 1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

                int ns = min(safe, dist[nx][ny]);
                if (ns > best[nx][ny]) {
                    best[nx][ny] = ns;
                    pq.push({ns, nx, ny});
                }
            }
        }

        return 0;
    }
};