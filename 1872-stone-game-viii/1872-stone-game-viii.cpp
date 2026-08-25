class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        // prefix sum
        for (int i = 1; i < n; ++i) {
            stones[i] += stones[i - 1];
        }

        // dp = best score difference starting from index i
        int dp = stones[n - 1];

        for (int i = n - 2; i >= 1; --i) {
            dp = max(dp, stones[i] - dp);
        }

        return dp;
    }
};