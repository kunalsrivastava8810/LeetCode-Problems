class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end()) << 1;

        vector<bool> pairXor(mx, false);

        // All XORs of two numbers
        for (int a : nums) {
            for (int b : nums) {
                pairXor[a ^ b] = true;
            }
        }

        vector<bool> ans(mx, false);

        // XOR with the third number
        for (int x = 0; x < mx; x++) {
            if (!pairXor[x]) continue;
            for (int c : nums) {
                ans[x ^ c] = true;
            }
        }

        return count(ans.begin(), ans.end(), true);
    }
};