class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int x = 0;
        for (int num : nums)
            x ^= num;

        if (x != 0)
            return nums.size();

        // Remove any one non-zero element.
        for (int num : nums) {
            if (num != 0)
                return nums.size() - 1;
        }

        // All elements are zero, so no non-empty subsequence
        // can have non-zero XOR.
        return 0;
    }
};