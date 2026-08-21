class Solution {
public:
    using ll = long long;

    long long lcmCap(long long a, long long b, long long limit) {
        // If lcm would exceed limit, we don't need its exact value.
        long long g = std::gcd(a, b);

        if (a / g > limit / b)
            return limit + 1;

        return a / g * b;
    }

    long long count(long long x, vector<int>& coins) {
        int n = coins.size();
        long long ans = 0;

        // Inclusion-Exclusion over all non-empty subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    l = lcmCap(l, coins[i], x);

                    if (l > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            long long multiples = x / l;

            if (bits & 1)
                ans += multiples;
            else
                ans -= multiples;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long lo = 1;

        // Every coin can generate multiples.
        // The kth amount is at most k * minimum coin.
        long long mn = *min_element(coins.begin(), coins.end());
        long long hi = mn * 1LL * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (count(mid, coins) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};