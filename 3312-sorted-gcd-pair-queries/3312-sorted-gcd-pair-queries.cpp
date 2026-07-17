class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1);
        for (int x : nums) freq[x]++;

        vector<long long> cntG(mx + 1);

        for (int g = mx; g >= 1; --g) {
            long long c = 0;
            for (int x = g; x <= mx; x += g) {
                c += freq[x];
                cntG[g] -= cntG[x];
            }
            cntG[g] += c * (c - 1) / 2;
        }

        vector<long long> pref(mx + 1);
        for (int i = 1; i <= mx; i++)
            pref[i] = pref[i - 1] + cntG[i];

        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            ans.push_back(upper_bound(pref.begin(), pref.end(), q) - pref.begin());
        }
        return ans;
    }
};