class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> ones;

        // Store positions of all '1's
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1')
                ones.push_back(i);
        }

        // Not enough 1s
        if (ones.size() < k)
            return "";

        string ans = "";

        // Consider every group of k consecutive 1s
        for (int i = 0; i + k - 1 < ones.size(); i++) {
            int l = ones[i];
            int r = ones[i + k - 1];

            string cur = s.substr(l, r - l + 1);

            if (ans.empty() ||
                cur.size() < ans.size() ||
                (cur.size() == ans.size() && cur < ans)) {
                ans = cur;
            }
        }

        return ans;
    }
};