class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        string half = "";
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half.append(cnt[i] / 2, char('a' + i));
            if (cnt[i] & 1)
                mid = char('a' + i);
        }

        string ans = half;
        if (mid)
            ans.push_back(mid);

        reverse(half.begin(), half.end());
        ans += half;

        return ans;
    }
};