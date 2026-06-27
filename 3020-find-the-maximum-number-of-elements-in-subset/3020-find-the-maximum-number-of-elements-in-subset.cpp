class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        int mx = 0;

        for (int x : nums) {
            freq[x]++;
            mx = max(mx, x);
        }

        int ans = 1;

        // Special case for 1
        if (freq.count(1)) {
            ans = freq[1];
            if (ans % 2 == 0) ans--;
        }

        for (auto &[val, cnt] : freq) {
            if (val == 1) continue;

            long long x = val;
            int len = 0;

            while (x <= mx && freq.count(x) && freq[x] >= 2) {
                len += 2;
                x *= x;
            }

            if (x <= mx && freq.count(x))
                len += 1;
            else
                len -= 1;

            ans = max(ans, len);
        }

        return ans;
    }
};