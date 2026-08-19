class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        // Store reserved seats as a bitmask for each affected row.
        for (auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            rows[row] |= (1 << col);
        }

        int ans = (n - rows.size()) * 2;

        // Masks for the three possible groups.
        int left  = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
        int mid   = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        int right = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

        for (auto& [row, mask] : rows) {
            bool canLeft  = (mask & left) == 0;
            bool canMid   = (mask & mid) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                ans += 2;
            } else if (canLeft || canMid || canRight) {
                ans += 1;
            }
        }

        return ans;
    }
};