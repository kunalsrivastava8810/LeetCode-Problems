class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // Only one type among remainder 1 and 2 exists
        if (min(cnt[1], cnt[2]) == 0) {
            return max(cnt[1], cnt[2]) > 2 && cnt[0] % 2 == 1;
        }

        // Both remainder 1 and 2 exist
        return abs(cnt[1] - cnt[2]) > 2 || cnt[0] % 2 == 0;
    }
};