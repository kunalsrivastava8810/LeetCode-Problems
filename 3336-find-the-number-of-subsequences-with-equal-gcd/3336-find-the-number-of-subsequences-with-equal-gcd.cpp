class Solution {
public:
    static constexpr int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        const int MAXG = 200;

        vector<vector<int>> dp(MAXG + 1, vector<int>(MAXG + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp = dp;  // option: ignore this element

            for (int g1 = 0; g1 <= MAXG; g1++) {
                for (int g2 = 0; g2 <= MAXG; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    int ng1 = (g1 == 0 ? x : std::gcd(g1, x));
                    ndp[ng1][g2] += dp[g1][g2];
                    if (ndp[ng1][g2] >= MOD) ndp[ng1][g2] -= MOD;

                    int ng2 = (g2 == 0 ? x : std::gcd(g2, x));
                    ndp[g1][ng2] += dp[g1][g2];
                    if (ndp[g1][ng2] >= MOD) ndp[g1][ng2] -= MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAXG; g++) {
            ans += dp[g][g];
        }

        return ans % MOD;
    }
};